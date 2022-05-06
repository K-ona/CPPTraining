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
