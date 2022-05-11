# 设计基于锁的并发数据结构

## 6.1 并发设计的意义

多线程环境下，无数据丢失和损毁，所有的数据需要维持原样，且无条件竞争的数据结构，称之为“线程安全”的数据结构。

本质上，在互斥量的保护下同一时间内只有一个线程可以获取锁。互斥量为了保护数据，会显式阻止线程对数据结构的并发访问。

串行化(serialzation)则是线程轮流访问数据，对数据进行串行访问。因此，需要对数据结构仔细斟酌，确保能进行真正的并发。虽然，有些数据结构比其他结构的并发访问范围更大，但思路都是一样的：减少保护区域，减少序列化操作，提升并发访问的能力。

### 6.1.1 并发数据结构设计的指南

设计并发数据结构时，需要考量两方面：一是确保访问安全，二是真正并发访问。

第三章关于线程安全的简单描述：

1. 确保无其他线程能够看到“不变量”变化时的状态。
2. 小心会引起条件竞争的接口，提供完整操作的函数，而非操作步骤。
3. 注意数据结构的行为是否会产生异常，从而确保“不变量”的状态。
4. 将死锁的概率降到最低。限制锁的范围，避免嵌套锁的存在。

还需要考虑数据结构对于使用者有什么限制，当线程通过特殊的函数对数据结构进行访问时，其他的线程还有哪些函数能安全调用？

如构造函数、析构函数、拷贝构造函数、赋值运算符、swap操作需要确保并发下是安全的。

关于真正的并发访问，可以考虑如下问题：

1. 操作在锁的范围中进行，是否允许在锁外执行？
2. 数据结构中不同的互斥量能否保护不同的区域？
3. 所有操作都需要同级互斥量的保护吗？
4. 能否对数据结构进行简单的修改后，使其并发访问能力更强？

这些问题都源于一个指导思想：如何让序列化访问最小化，让真正的并发最大化？

最简单的线程安全结构通常会对数据使用互斥量或锁。虽然，这么做还有问题，不过这样做相对简单，并且能保证只有一个线程在同一时间对数据结构进行独立访问。为了更轻松的设计线程安全的数据结构，接下来了解一下基于锁的数据结构

## 6.2 基于锁的并发数据结构

基于锁的并发数据结构需要确保访问线程持有锁的时间最短，不需要锁的操作不能访问共享数据，确保不会产生条件竞争，当操作需要获取多个互斥锁时，可能会产生死锁，所以使用多个互斥量时要格外小心。

### 6.2.1 线程安全栈——使用锁

代码6.1 线程安全栈的类定义

````` cpp
#include <exception>
struct empty_stack : std::exception {
  const char* what() const throw();
};

template <typename T>
class threadsafe_stack {
 private:
  std::stack<T> data;
  mutable std::mutex m;

 public:
  threadsafe_stack() {}
  threadsafe_stack(const threadsafe_stack& other) {
    std::lock_guard<std::mutex> lock(other.m);
    data = other.data;
  }

  threadsafe_stack& operator=(const threadsafe_stack&) = delete;
  void push(T new_value) {
    std::lock_guard<std::mutex> lock(m);
    data.push(std::move(new_value));  // 1
  }

  std::shared_ptr<T> pop() {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) // ? 调用empty时又 对m进行加锁，为未定义行为
      throw empty_stack();  // 2 
    std::shared_ptr<T> const res(
        std::make_shared<T>(std::move(data.top())));  // 3
    data.pop();                                       // 4
    return res;
  }

  void pop(T& value) {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty())
      throw empty_stack();
    value = std::move(data.top());  // 5
    data.pop();                     // 6
  }

  bool empty() const {
    std::lock_guard<std::mutex> lock(m);
    return data.empty();
  }
};
`````

### 6.2.2 线程安全队列——使用锁和条件变量

代码6.2 使用条件变量实现的线程安全队列

  ```` cpp
  template <typename T>
  class threadsafe_queue {
  private:
    mutable std::mutex mut;
    std::queue<T> data_queue;
    std::condition_variable data_cond;

  public:
    threadsafe_queue() {}

    void push(T data) {
      std::lock_guard<std::mutex> lk(mut);
      data_queue.push(std::move(data));
      data_cond.notify_one();  // 1
    }

    void wait_and_pop(T& value)  // 2
    {
      std::unique_lock<std::mutex> lk(mut);
      data_cond.wait(lk, [this] { return !data_queue.empty(); });
      value = std::move(data_queue.front());
      data_queue.pop();
    }

    std::shared_ptr<T> wait_and_pop()  // 3
    {
      std::unique_lock<std::mutex> lk(mut);
      data_cond.wait(lk, [this] { return !data_queue.empty(); });  // 4
      std::shared_ptr<T> res(std::make_shared<T>(std::move(data_queue.front())));
      data_queue.pop();
      return res;
    }

    bool try_pop(T& value) {
      std::lock_guard<std::mutex> lk(mut);
      if (data_queue.empty())
        return false;
      value = std::move(data_queue.front());
      data_queue.pop();
      return true;
    }

    std::shared_ptr<T> try_pop() {
      std::lock_guard<std::mutex> lk(mut);
      if (data_queue.empty())
        return std::shared_ptr<T>();  // 5
      std::shared_ptr<T> res(std::make_shared<T>(std::move(data_queue.front())));
      data_queue.pop();
      return res;
    }

    bool empty() const {
      std::lock_guard<std::mutex> lk(mut);
      return data_queue.empty();
    }
  };
  ````

代码6.3 持有 std::shared_ptr<> 实例的线程安全队列基于6.2的异常安全版本

  ```` cpp
  template <typename T>
  class threadsafe_queue {
  private:
    mutable std::mutex mut;
    std::queue<std::shared_ptr<T> > data_queue;
    std::condition_variable data_cond;

  public:
    threadsafe_queue() {}
    void wait_and_pop(T& value) {
      std::unique_lock<std::mutex> lk(mut);
      data_cond.wait(lk, [this] { return !data_queue.empty(); });
      value = std::move(*data_queue.front());  // 1
      data_queue.pop();
    }
    bool try_pop(T& value) {
      std::lock_guard<std::mutex> lk(mut);
      if (data_queue.empty())
        return false;
      value = std::move(*data_queue.front());  // 2
      data_queue.pop();
      return true;
    }
    std::shared_ptr<T> wait_and_pop() {
      std::unique_lock<std::mutex> lk(mut);
      data_cond.wait(lk, [this] { return !data_queue.empty(); });
      std::shared_ptr<T> res = data_queue.front();  // 3
      data_queue.pop();
      return res;
    }
    std::shared_ptr<T> try_pop() {
      std::lock_guard<std::mutex> lk(mut);
      if (data_queue.empty())
        return std::shared_ptr<T>();
      std::shared_ptr<T> res = data_queue.front();  // 4
      data_queue.pop();
      return res;
    }
    void push(T new_value) {
      std::shared_ptr<T> data(std::make_shared<T>(std::move(new_value)));  // 5 ：因为内存分配需要 在性能上付出很高的代价(性能较低)，因为减少了互斥量持有的时间，所以 std::shared_ptr<> 对队列的性能有很大的提升，并且允许其他线程在分配内存的同时，可以对队列进行其他操作。
      std::lock_guard<std::mutex> lk(mut);
      data_queue.push(data);
      data_cond.notify_one();
    }
    bool empty() const {
      std::lock_guard<std::mutex> lk(mut);
      return data_queue.empty();
    }
  };
  ````

如同栈的例子一样，使用互斥量保护整个数据结构，不过会限制队列对并发的支持。虽然成员函数会阻塞多线程，但仍有一个线程能在任意时间内进行工作。不过，因为使用标准容器的原因，数据处于保护中(这种限制是实现中使用了 std::queue<> )，要对数据结构进行具体的控制，需要提供更多细粒度锁，来完成更高级的并发。

### 6.2.3 线程安全队列——使用细粒度锁和条件变量

代码6.4 基于链表的队列实现——单线程版

  ```` cpp
  template <typename T>
  class queue {
  private:
    struct node {
      T data;
      std::unique_ptr<node> next;
      node(T data_) : data(std::move(data_)) {}
    };
    std::unique_ptr<node> head;  // 1
    node* tail;                  // 2
  public:
    queue() {}
    queue(const queue& other) = delete;
    queue& operator=(const queue& other) = delete;
    std::shared_ptr<T> try_pop() {
      if (!head) {
        return std::shared_ptr<T>();
      }
      std::shared_ptr<T> const res(std::make_shared<T>(std::move(head->data)));
      std::unique_ptr<node> const old_head = std::move(head);
      head = std::move(old_head->next);  // 3
      return res;
    }
    void push(T new_value) {
      std::unique_ptr<node> p(new node(std::move(new_value)));
      node* const new_tail = p.get();
      if (head) {
        tail->next = std::move(p);  // 4
      } else {
        head = std::move(p);  // 5
      }
      tail = new_tail;  // 6
    }
  };
  ````

虽然，这种实现对于单线程来说没什么问题，但当在多线程下尝试使用细粒度锁时，就会出现问题。因为在给定的实现中有两个数据项(head①和tail②)，即便是使用两个互斥量来保护头指针和尾指针，也会出现问题。

**通过分离数据实现并发**

可以使用“预分配虚拟节点(无数据)，确保这个节点永远在队列的最后，用来分离头尾指针能访问的节点”的办法。对于一个空队列来说，head和tail都属于虚拟指针，而非空指针。因为当队列为空时，try_pop()不能访问head->next了。当添加一个节点入队列时(这时有真实节点了)，head和tail现在指向不同的节点，所以就不会在head->next和tail->next上产生竞争。缺点是，必须额外添加一个间接层次的指针数据来做虚拟节点。

代码6.5 带有虚拟节点的队列

  ```` cpp
  template <typename T>
  class queue {
  private:
    struct node {
      std::shared_ptr<T> data;  // 1
      std::unique_ptr<node> next;
    };
    std::unique_ptr<node> head;
    node* tail;

  public:
    queue()
        : head(new node),
          tail(head.get())  // 2
    {}
    queue(const queue& other) = delete;
    queue& operator=(const queue& other) = delete;

    std::shared_ptr<T> try_pop() {
      if (head.get() == tail)  // 3
      {
        return std::shared_ptr<T>();
      }
      std::shared_ptr<T> const res(head->data);  // 4
      std::unique_ptr<node> old_head = std::move(head);
      head = std::move(old_head->next);  // 5
      return res;                        // 6
    }

    void push(T new_value) {
      std::shared_ptr<T> new_data(
          std::make_shared<T>(std::move(new_value)));  // 7
      std::unique_ptr<node> p(new node);               // 8
      tail->data = new_data;                           // 9
      node* const new_tail = p.get();
      tail->next = std::move(p);
      tail = new_tail;
    }
  };
  ````

现在的`push()`只能访问`tail`，而不能访问`head`，`try_pop()`可以访问`head`和`tail`，但是`tail`只需在最开始进行比较，所以锁存在的时间很短。重大的提升在于虚拟节点意味着`try_pop()`和`push()`不能对同一节点进行操作，所以不再需要互斥了。现在，只需要使用互斥量来分别保护`head`和`tail`就够了。

代码6.6 线程安全队列——细粒度锁版

  ```` cpp
  template <typename T>
  class threadsafe_queue {
  private:
    struct node {
      std::shared_ptr<T> data;
      std::unique_ptr<node> next;
    };

    std::mutex head_mutex;
    std::mutex tail_mutex;
    std::unique_ptr<node> head;
    node* tail;

    node* get_tail() {
      std::lock_guard<std::mutex> tail_lock(tail_mutex);
      return tail;
    }

    std::unique_ptr<node> pop_head() {
      std::lock_guard<std::mutex> head_lock(head_mutex);
      if (head.get() == get_tail()) { // 需在 head_mutex 上锁之后
        return nullptr;
      }
      std::unique_ptr<node> old_head = std::move(head);
      head = std::move(old_head->next);
      return old_head;
    }

  public:
    threadsafe_queue() : head(new node), tail(head.get()) {}

    threadsafe_queue(const threadsafe_queue& other) = delete;
    threadsafe_queue& operator=(const threadsafe_queue& other) = delete;

    std::shared_ptr<T> try_pop() {
      std::unique_ptr<node> old_head = pop_head();
      return old_head ? old_head->data : std::shared_ptr<T>();
    }

    void push(T new_value) {
      std::shared_ptr<T> new_data(std::make_shared<T>(std::move(new_value)));
      std::unique_ptr<node> p(new node);
      node* const new_tail = p.get();
      std::lock_guard<std::mutex> tail_lock(tail_mutex);
      tail->data = new_data;
      tail->next = std::move(p);
      tail = new_tail;
    }
  };
  ````

异常是很有趣的东西。虽然，已经改变了数据的分配模式，但是异常可能从别的地方来袭。try_pop()中的对锁的操作会产生异常，并直到获取锁才能对数据进行修改，try_pop()是异常安全的。

另一方面，push()可以在堆上新分配出一个T的实例，以及node的新实例，这里可能会抛出异常。但是，所有分配的对象都赋给了智能指针，当异常发生时就会被释放掉。一旦获取锁，push()就不会抛出异常，所以也是异常安全的。

**实现代码6.2中的 `wait_and_pop()`**

使用细粒度锁是为了保证最大程度的并发。当互斥量和 `notify_one()` 混用时，如果通知线程在互斥量解锁后唤醒调用 `notify_one()` ，那么线程就需要等待互斥量上锁。另一方面，解锁操作在 `notify_one()` 之前调用时，互斥量可能会等待线程醒来获取互斥锁(假设没有其他线程对互斥量上锁)。这可能是一个微小的改动，但对于某些情况来说就很重要。

代码6.7 可上锁和等待的线程安全队列——内部结构及接口

  ```` cpp
  template <typename T>
  class threadsafe_queue {
  private:
    struct node {
      std::shared_ptr<T> data;
      std::unique_ptr<node> next;
    };
    std::unique_ptr<node> head;
    node* tail;

    std::mutex head_mutex;
    std::mutex tail_mutex;
    std::condition_variable data_cond;

  public:
    threadsafe_queue() : head(new node), tail(head.get()) {}

    threadsafe_queue(const threadsafe_queue& other) = delete;
    threadsafe_queue& operator=(const threadsafe_queue& other) = delete;

    std::shared_ptr<T> try_pop();
    bool try_pop(T& value);
    std::shared_ptr<T> wait_and_pop();
    void wait_and_pop(T& value);

    void push(T new_value);
    bool empty();
  };
  ````

代码6.8 可上锁和等待的线程安全队列——推入新节点

  ```` cpp
  template <typename T>
  void threadsafe_queue<T>::push(T new_value) {
    std::shared_ptr<T> new_data(std::make_shared<T>(std::move(new_value)));
    std::unique_ptr<node> p(new node);
    {
      std::lock_guard<std::mutex> tail_lock(tail_mutex);
      tail->data = new_data;
      node* const new_tail = p.get();
      tail->next = std::move(p);
      tail = new_tail;
    }
    data_cond.notify_one();
  }
  ````

代码6.9 可上锁和等待的线程安全队列——wait_and_pop()

  ```` cpp
  template <typename T>
  class threadsafe_queue {
  private:
    node* get_tail() {
      std::lock_guard<std::mutex> tail_lock(tail_mutex);
      return tail;
    }
    std::unique_ptr<node> pop_head()  // 1
    {
      std::unique_ptr<node> old_head = std::move(head);
      head = std::move(old_head->next);
      return old_head;
    }
    std::unique_lock<std::mutex> wait_for_data()  // 2
    {
      std::unique_lock<std::mutex> head_lock(head_mutex);
      data_cond.wait(head_lock, [&] { return head.get() != get_tail(); });
      return head_lock;  // 3
    }
    std::unique_ptr<node> wait_pop_head() {
      std::unique_lock<std::mutex> head_lock(wait_for_data());  // 4
      return pop_head();
    }
    std::unique_ptr<node> wait_pop_head(T& value) {
      std::unique_lock<std::mutex> head_lock(wait_for_data());  // 5
      value = std::move(*head->data);
      return pop_head();
    }

  public:
    std::shared_ptr<T> wait_and_pop() {
      std::unique_ptr<node> const old_head = wait_pop_head();
      return old_head->data;
    }
    void wait_and_pop(T& value) {
      std::unique_ptr<node> const old_head = wait_pop_head(value);
    }
  };
  ````

代码6.10 可上锁和等待的线程安全队列——try_pop()和empty()

  ```` cpp
  template <typename T>
  class threadsafe_queue {
  private:
    std::unique_ptr<node> try_pop_head() {
      std::lock_guard<std::mutex> head_lock(head_mutex);
      if (head.get() == get_tail()) {
        return std::unique_ptr<node>();
      }
      return pop_head();
    }
    std::unique_ptr<node> try_pop_head(T& value) {
      std::lock_guard<std::mutex> head_lock(head_mutex);
      if (head.get() == get_tail()) {
        return std::unique_ptr<node>();
      }
      value = std::move(*head->data);
      return pop_head();
    }

  public:
    std::shared_ptr<T> try_pop() {
      std::unique_ptr<node> old_head = try_pop_head();
      return old_head ? old_head->data : std::shared_ptr<T>();
    }
    bool try_pop(T& value) {
      std::unique_ptr<node> const old_head = try_pop_head(value);
      return old_head;
    }
    bool empty() {
      std::lock_guard<std::mutex> head_lock(head_mutex);
      return (head.get() == get_tail());
    }
  };
  ````

## 6.3 设计更加复杂的数据结构

先来看看，在设计查询表时遇到的一些问题。

### 6.3.1 使用锁的线程安全查询表

查询表或字典是一种类型的值(键值)和另一种类型的值进行关联(映射)的数据结构。一般情况下，这样的结构允许代码通过键值对相关的数据值进行查询。C++标准库中相关工具： `std::map<>` , `std::multimap<>` , `std::unordered_map<>` 和 `std::unordered_multimap<>`

和队列和栈一样，标准容器的接口不适合多线程进行并发访问，因为这些接口都存在固有的条件竞争，所以有些接口需要砍掉或重新修订。

并发访问时， `std::map<>` 的最大问题在于迭代器，可能会碰到下面的问题：迭代器引用的元素被其他线程删除时，迭代器就会出问题。线程安全的查询表的第一次接口削减，需要绕过迭代器。

`std::map<>` (以及标准库中其他相关容器)给定的接口对于迭代器的依赖很严重，其中有些接口需要先放
在一边，先对一些简单接口进行设计。查询表的基本操作有：

- 添加一对键值对
- 修改指定键值对应的数据
- 删除一对键值对
- 通过给定键值，获取对应数据

最有可能的条件竞争在于，当一对“键值-数据”加入时。当两个线程都修改一个数据，那么肯定一先一后。那么一种方式是合并“添加”和“修改”操作，为一个成员函数。

**为细粒度锁设计映射结构**

三个常见关联容器的方式：

- 二叉树，比如：红黑树
  二叉树的方式，不会提高并发访问的能力。每一个查找或者修改操作都需要访问根节点，所以根节点需要上锁。虽然访问线程在向下移动时，锁可以进行释放，但相比横跨整个数据结构的单锁，并没有什么优势。
- 有序数组
  有序数组是最坏的选择，因为无法提前言明数组中哪段是有序的，所以需要用一个锁将整个数组锁起来。
- 哈希表
  假设有固定数量的桶，每个桶都有一个键值(关键特性)，以及散列函数。这就意味着你可以安全的对每个桶上锁。当再次使用互斥量(支持多读者单作者)时，就能将并发访问的可能性增加N倍，这里N是桶的数量。当然，缺点也是有的：对于键值的操作，需要有合适的函数。C++标准库提供 `std::hash<>` 模板，可以直接使用，用户还可以简单的对键值类型进行特化。如果去效仿标准无序容器，并且获取函数对象的类型作为哈希表的模板参数，用户可以选择特化 `std::hash<>` 的键值类型，或者直接提供哈希函数。

代码6.11 线程安全的查询表

  ```` cpp
  #include <unordered_map>
  #include <vector>
  #include <list>
  #include <mutex>
  #include <shared_mutex>
  #include <memory>

  template <typename Key, typename Value, typename Hash = std::hash<Key> >
  class threadsafe_lookup_table {
  private:
    class bucket_type {
    private:
      typedef std::pair<Key, Value> bucket_value;
      typedef std::list<bucket_value> bucket_data;
      typedef typename bucket_data::iterator bucket_iterator;
      bucket_data data;
      mutable std::shared_mutex mutex;                      // 1
      bucket_iterator find_entry_for(Key const& key) const  // 2
      {
        return std::find_if(
            data.begin(), data.end(),
            [&](bucket_value const& item) { return item.first == key; });
      }

    public:
      Value value_for(Key const& key, Value const& default_value) const {
        std::shared_lock<std::shared_mutex> lock(mutex);  // 3
        bucket_iterator const found_entry = find_entry_for(key);
        return (found_entry == data.end()) ? default_value : found_entry->second;
      }
      void add_or_update_mapping(Key const& key, Value const& value) {
        std::unique_lock<std::shared_mutex> lock(mutex);  // 4
        bucket_iterator const found_entry = find_entry_for(key);
        if (found_entry == data.end()) {
          data.push_back(bucket_value(key, value));
        } else {
          found_entry->second = value;
        }
      }
      void remove_mapping(Key const& key) {
        std::unique_lock<std::shared_mutex> lock(mutex);  // 5
        bucket_iterator const found_entry = find_entry_for(key);
        if (found_entry != data.end()) {
          data.erase(found_entry);
        }
      }
    };

    std::vector<std::unique_ptr<bucket_type>> buckets;  // 6
    Hash hasher;
    bucket_type& get_bucket(Key const& key) const  // 7
    {
      std::size_t const bucket_index = hasher(key) % buckets.size();
      return *buckets[bucket_index];
    }

  public:
    typedef Key key_type;
    typedef Value mapped_type;
    typedef Hash hash_type;
    threadsafe_lookup_table(unsigned num_buckets = 19,
                            Hash const& hasher_ = Hash())
        : buckets(num_buckets), hasher(hasher_) {
      for (unsigned i = 0; i < num_buckets; ++i) {
        buckets[i].reset(new bucket_type);
      }
    }
    threadsafe_lookup_table(threadsafe_lookup_table const& other) = delete;
    threadsafe_lookup_table& operator=(threadsafe_lookup_table const& other) = delete;
    Value value_for(Key const& key, Value const& default_value = Value()) const {
      return get_bucket(key).value_for(key, default_value);  // 8
    }
    void add_or_update_mapping(Key const& key, Value const& value) {
      get_bucket(key).add_or_update_mapping(key, value);  // 9
    }
    void remove_mapping(Key const& key) {
      get_bucket(key).remove_mapping(key);  // 10
    }
  };
  ````

从并发的角度考虑，互斥锁保护所有成员，这样的实现是“异常安全”的吗？ value_for 是不能修改任何值的，所以其不会有问题。如果value_for抛出异常，也不会影响任何数据结构。remove_mapping 修改链表时，会调用 erase ，不过这能保证没有异常抛出。那么就剩 add_or_update_mapping 了，可能会在其两个if分支上抛出异常。 push_back 是异常安全的，如果有异常抛出，也会将链表恢复成原始状态。唯一的问题就在赋值阶段(将替换已有的数据)，当赋值阶段抛出异常，用于依赖的原始状态没有改变，所以不会影响数据结构的整体,以及用户提供类型的属性，这样就可以放心的将问题交给用户处理。

### 6.3.2 编写使用锁的线程安全链表

代码6.13 线程安全链表——支持迭代器

  ```` cpp
  #include <unordered_map>
  #include <vector>
  #include <list>
  #include <mutex>
  #include <shared_mutex>
  #include <memory>

  template<typename T>
  class threadsafe_list {
    struct node { // 1
      std::mutex m; 
      std::shared_ptr<T> data; 
      std::unique_ptr<node> next; 

      node() :  {} //2
      node(const T& value) : data(std::make_shared<T>(value)) {} // 3
    };

    node head; 
  
  public:
    threadsafe_list() {}
    ~threadsafe_list() {
      remove_if( [](const node&){
        return true; 
      } )
    }

    threadsafe_list(const threadsafe_list& other) = delete; 
    threadsafe_list& operator=(const threadsafe_list& other) = delete; 

    void push_front(const T& value) {
      std::unique_ptr<node> new_node(new node(value));  // 4
      std::lock_guard<std::mutex> lk(head.m); 
      new_node->next = std::move(head->next); // 5
      head->next = new_node;  //  6
    }

    template<typename Function>
    void for_each(Function f) { // 7
      node* current = &head; 
      std::unique_lock<std::mutex> lk(head.m); // 8
      while (node* next = current->next.get()) { // 9
        std::unique_lock<std::mutex> next_lk(next->m);  // 10
        lk.unlock();  // 11
        f(*next->data); // 12
        current = next; 
        lk = std::move(next_lk); // 13
      }
    }

    template<typename Predicate>
    std::shared_ptr<T> find_first_if(Predicate p) { // 14
      node* current = &head;
      std::unique_lock<std::mutex> lk(head.m); 
      while (node* next = current->next.get()) {
        std::unique_lock<std::mutex> next_lk(next->m); 
        if (p(*next->data)) { // 15
          return next->data;  // 16
        }
        current = next; 
        lk = std::move(next_lk); 
      }
      return std::shared_ptr<T>(); 
    }


    template<typename Predicate>
    void remove_if(Predicate p) { // 17 
      node* current = &head; 
      std::unique_lock<std::mutex> lk(head.m); 
      while (const node* next = current->next.get()) {
        std::unique_lock<std::mutex> next_lk(next->m); 
        if (p(*next->data)) { // 18
          std::unique_ptr<node> tmp = std::move(current->next); 
          current->next = std::move(next->next); 
          next_lk.unlock(); 
        } else { // 20
          lk.unlock();  // 21
          current = next; 
          lk = std::move(next_lk); 
        }
      }
    }
  }; 
  ````
