# 3 共享数据

## 3.1 共享数据的问题

问题在于共享数据的修改，如果数据是只读的，就不会出现问题
并行中常见的错误：条件竞争(race condition)
C++标准定义了data race, 一种特殊的条件竞争：并发的修改同一个独立对象

不变量：对于特殊结构的描述
例如，二叉搜索树每个节点的不变量，左节点的key总是小于右节点的key

### 3.1.1 条件竞争

### 3.1.2 避免恶性条件竞争

1. 保护数据结构（如使用锁）

2. 修改数据结构的行为不可分割（无锁编程），不变量的状态得到了保证

3. 软件事务内存 (software transactional memory (STM))

## 3.2 使用互斥量

互斥量是C++保护数据最通用的机制，但也需要编排代码来保护数据的正确性(见3.2.2节)，避免接口间的条件竞争(见3.2.3节)也非常重要。
不过，互斥量也会造成死锁(见3.2.4节)，或对数据保护的太多(或太少)(见3.2.8节)

### 3.2.1 互斥量
通过实例化 std::mutex 创建互斥量实例，成员函数lock()可对互斥量上锁，unlock()为解锁。
不过，不推荐直接去调用成员函数，调用成员函数就意味着，必须在每个函数出口都要去调用unlock()(包括异常的情况)。
C++标准库为互斥量提供了RAII模板类 std::lock_guard，在构造时就能提供已锁的互斥量，并在析构时进行解锁，从而保证了互斥量能被正确解锁。
下面的代码中，展示了如何在多线程应用中，使用 std::mutex 构造的 std::lock_guard 实例，对列表进行访问保护。

  ```` cpp
  #include <mutex>
  #include <algorithm>
  std::list<int> some_list; // 1
  std::mutex some_mutex; // 2
  void add_to_list(int new_value)
  {
    std::lock_guard<std::mutex> guard(some_mutex); // 3
    some_list.push_back(new_value);
  }
  bool list_contains(int value_to_find)
  {
    std::lock_guard<std::mutex> guard(some_mutex); // 4
    return std::find(some_list.begin(),some_list.end(),value_to_find) !=
    some_list.end();
  }
  ````

**C++17中添加了一个新特性，称为模板类参数推导**，类似 std::lock_guard 这样简单的模板类型，其模板参数列表可以省略。③和④的代码可以简化成：
  
  ```` cpp
  std::lock_guard guard(some_mutex);
  ````

C++17还提供了一种加强版数据保护机制—— std::scoped_lock
所以上面这行代码也可以写成：
  
  ```` cpp
  std::scoped_lock guard(some_mutex);
  ````

### 3.2.2 保护共享数据

1. 确保成员函数不会传出指针或引用的同时，检查成员函数是否通过指针或引用的方式来调用也是很重要的
2. 函数可能没在互斥量保护的区域内存储指针或引用
3. 将保护数据作为一个运行时参数

代码3.2 无意中传递了保护数据的引用

  ```` cpp
  class some_data {
    int a;
    std::string b;

  public:
    void do_something();
  };
  class data_wrapper {
  private:
    some_data data;
    std::mutex m;

  public:
    template <typename Function>
    void process_data(Function func) {
      std::lock_guard<std::mutex> l(m);
      func(data);  // 1 传递“保护”数据给用户函数
    }
  };
  some_data* unprotected;
  void malicious_function(some_data& protected_data) {
    unprotected = &protected_data;
  }
  data_wrapper x;
  void foo() {
    x.process_data(malicious_function);  // 2 传递一个恶意函数
    unprotected->do_something();  // 3 在无保护的情况下访问保护数据
  }
  ````

### 3.2.3 接口间的条件竞争

即使使用了互斥量或其他机制保护了共享数据，也可能出现条件竞争。

代码3.3 std::stack 容器的实现

  ```` cpp
  template <typename T, typename Container = std::deque<T> >
  class stack {
  public:
    explicit stack(const Container&);
    explicit stack(Container&& = Container());
    template <class Alloc>
    explicit stack(const Alloc&);
    template <class Alloc>
    stack(const Container&, const Alloc&);
    template <class Alloc>
    stack(Container&&, const Alloc&);
    template <class Alloc>
    stack(stack&&, const Alloc&);
    bool empty() const;
    size_t size() const;
    T& top();
    T const& top() const;
    void push(T const&);
    void push(T&&);
    void pop();
    void swap(stack&&);
    template <class... Args> void emplace(Args&&... args); // C++14的新特性
  };
  ````

考虑如下场景

  ```` cpp
  stack<int> s;
  if (! s.empty()){ // 1
    int const value = s.top(); // 2
    s.pop(); // 3
    do_something(value);
  }
  ````

在调用 empty() 和调用 top() 之间，可能有来自另一个线程的 pop() 调用并删除了最后一个元素
这是一个经典的条件竞争，使用互斥量对栈内部数据进行保护，但依旧不能阻止条件竞争的发生，这就是接口固有的问题

同时可能还存在两个线程同时拿到 s.top() 的值，然后 s.pop() 了两次

1. 传入一个引用
  第一个选项是将变量的引用作为参数，传入pop()函数中获取“弹出值”:

    ```` cpp
    std::vector<int> result;
    some_stack.pop(result);
    ````
  
  缺点也很明显：需要构造出一个栈中类型的实例，用于接收目标值。对于一些类型，这样做是不现实的，因为临时构造一个实例，从时间和资源的角度上来看都不划算。对于其他的类型，这样也不总行得通，因为构造函数需要的参数，在这个阶段不一定可用。最后，需要可赋值的存储类型，这是一个重大限制：即使支持移动构造，甚至是拷贝构造(从而允许返回一个值)，很多用户自定义类型可能都不支持赋值操作。
2. 无异常抛出的拷贝构造函数或移动构造函数
对于有返回值的pop()函数来说，只有“异常安全”方面的担忧(当返回值时可以抛出一个异常)。
3. 返回指向弹出值的指针( `std::shared_ptr<T>` )
4. “选项1 + 选项2” 或 “选项1 + 选项3”

  代码3.4 线程安全的stack类定义(概述)

  ```` cpp
  #include <exception>
  #include <memory> // For std::shared_ptr<>
  struct empty_stack: std::exception
  {
    const char* what() const throw();
  };

  template<typename T>
  class threadsafe_stack
  {
  public:
    threadsafe_stack();
    threadsafe_stack(const threadsafe_stack&);
    threadsafe_stack& operator=(const threadsafe_stack&) = delete; // 1 赋值操作被删除
    void push(T new_value);
    std::shared_ptr<T> pop();
    void pop(T& value);
    bool empty() const;
  };
  ````

  代码3.5 扩充(线程安全)stack

  ```` cpp
  #include <exception>
  #include <memory>
  #include <mutex>
  #include <stack>
  struct empty_stack : std::exception {
    const char* what() const throw() { return "empty stack!"; };
  };
  template <typename T>
  class threadsafe_stack {
  private:
    std::stack<T> data;
    mutable std::mutex m;

  public:
    threadsafe_stack() : data(std::stack<T>()) {}
    threadsafe_stack(const threadsafe_stack& other) {
      std::lock_guard<std::mutex> lock(other.m);
      data = other.data;  // 1 在构造函数体中的执行拷贝
    }
    threadsafe_stack& operator=(const threadsafe_stack&) = delete;
    void push(T new_value) {
      std::lock_guard<std::mutex> lock(m);
      data.push(new_value);
    }
    std::shared_ptr<T> pop() {
      std::lock_guard<std::mutex> lock(m);
      if (data.empty())
        throw empty_stack();  // 在调用pop前，检查栈是否为空
      std::shared_ptr<T> const res(std::make_shared<T>(data.top()));  // 在修改栈前，分配出返回值
      data.pop();
      return res;
    }
    void pop(T& value) {
      std::lock_guard<std::mutex> lock(m);
      if (data.empty())
        throw empty_stack();
      value = data.top();
      data.pop();
    }
    bool empty() const {
      std::lock_guard<std::mutex> lock(m);
      return data.empty();
    }
  };
  ````

通过增大锁的粒度缓解了恶性条件竞争
不过锁的粒度过大会导致性能问题
锁的粒度太小，一个给定操作操作需要两个或更多的锁，可能会导致出现一个潜在的死锁问题

### 3.2.4 死锁

避免死锁的一般建议，

1. 让互斥量以相同的顺序上锁：总在互斥量B之前锁住互斥量A，就永远不会死锁。

2. 同时对所有互斥量加锁

std::lock ——可以一次性锁住多个(两个以上)的互斥量，并且没有副作用(死锁风险)

代码3.6 交换操作中使用 std::lock() 和 std::lock_guard<>

```` cpp

// 这里的std::lock()需要包含<mutex>头文件
class some_big_object;

void swap(some_big_object& lhs,some_big_object& rhs);

class X
{
private:
  some_big_object some_detail;
  std::mutex m;
public:
  X(some_big_object const& sd):some_detail(sd){}
  friend void swap(X& lhs, X& rhs)
  {
    if(&lhs==&rhs)
      return;
    std::lock(lhs.m,rhs.m); // 1
    std::lock_guard<std::mutex> lock_a(lhs.m,std::adopt_lock); // 2
    std::lock_guard<std::mutex> lock_b(rhs.m,std::adopt_lock); // 3
    swap(lhs.some_detail,rhs.some_detail);
  }
};
````

std::scoped_lock<> 是一种新的RAII模板类型，与 std::lock_guard<> 的功能相同，这个新类型能接受不定数量的互斥量类型作为模板参数，以及相应的互斥量(数量和类型)作为构造参数。
互斥量支持构造时上锁，与 std::lock 的用法相同，解锁在析构中进行。

```` cpp
// c++ 17新增 std::scoped_lock<> 

void swap(X& lhs, X& rhs)
{
  if(&lhs==&rhs)
  return;
  std::scoped_lock guard(lhs.m,rhs.m); // 1
  swap(lhs.some_detail,rhs.some_detail);
}

````

虽然 std::lock (和 std::scoped_lock<> )可以在这情况下(获取两个以上的锁)避免死锁，但它没办法帮助你获取其中一个锁。这需要依赖开发者的纪律性(译者：也就是经验)，来确保程序不会死锁。

### 3.2.5 避免死锁的建议

1. 避免嵌套锁
第一个建议往往是最简单的：线程获得一个锁时，就别再去获取第二个。每个线程只持有一个锁，就不会产生死锁。当需要获取多个锁，使用 std::lock 来做这件事(对获取锁的操作上锁)，避免产生死锁。

2. 避免在持有锁时调用外部代码
第二个建议是次简单的：因为代码是外部提供的，所以没有办法确定外部要做什么。
外部程序可能做任何事情，包括获取锁。在持有锁的情况下，如果用外部代码要获取一个锁，就会违反第一个指导意见，并造成死锁(有时这是无法避免的)。
当写通用代码时(例如3.2.3中的栈)，每一个操作的参数类型，都是外部提供的定义，这就需要其他指导意见来帮助你了。

3. 使用固定顺序获取锁
当硬性要求获取两个或两个以上的锁，并且不能使用 std::lock 单独操作来获取它们时，最好在每个线程上，
用固定的顺序获取它们(锁)

4. 使用层次锁结构
虽然，定义锁的顺序是一种特殊情况，但层次锁的意义在于，在运行时会约定是否进行检查。这个建议需要**对应用进行分层**，并且识别在给定层上所有互斥量。当代码试图对互斥量上锁，而低层已持有该层锁时，不允许锁定。可以通过每个互斥量对应的层数，以及每个线程使用的互斥量，在运行时检查锁定操作是否可以进行。下面的代码列表中，展示两个线程如何使用进行分层互斥的

代码3.7 使用层次锁来避免死锁

```` cpp

hierarchical_mutex high_level_mutex(10000); // 1
hierarchical_mutex low_level_mutex(5000); // 2
hierarchical_mutex other_mutex(6000); // 3

int do_low_level_stuff();
int low_level_func()
{
  std::lock_guard<hierarchical_mutex> lk(low_level_mutex); // 4
  return do_low_level_stuff();
}

void high_level_stuff(int some_param);
void high_level_func()
{
  std::lock_guard<hierarchical_mutex> lk(high_level_mutex); // 6
  high_level_stuff(low_level_func()); // 5
}

void thread_a() // 7
{
  high_level_func();
}

void do_other_stuff();
void other_stuff()
{
  high_level_func(); // 10
  do_other_stuff();
}

void thread_b() // 8
{
  std::lock_guard<hierarchical_mutex> lk(other_mutex); // 9
  other_stuff();
}
````

hierarchical_mutex 的简单实现

```` cpp
class hierarchical_mutex {
  std::mutex internal_mutex;
  unsigned long const hierarchy_value;
  unsigned long previous_hierarchy_value;
  static thread_local unsigned long this_thread_hierarchy_value;  // 1
  void check_for_hierarchy_violation() {
    if (this_thread_hierarchy_value <= hierarchy_value)  // 2
    {
      throw std::logic_error(“mutex hierarchy violated”);
    }
  }
  void update_hierarchy_value() {
    previous_hierarchy_value = this_thread_hierarchy_value;  // 3
    this_thread_hierarchy_value = hierarchy_value;
  }

 public:
  explicit hierarchical_mutex(unsigned long value)
      : hierarchy_value(value), previous_hierarchy_value(0) {}
  void lock() {
    check_for_hierarchy_violation();
    internal_mutex.lock();     // 4
    update_hierarchy_value();  // 5
  }
  void unlock() {
    if (this_thread_hierarchy_value != hierarchy_value)
      throw std::logic_error(“mutex hierarchy violated”);    // 9
    this_thread_hierarchy_value = previous_hierarchy_value;  // 6
    internal_mutex.unlock();
  }
  bool try_lock() {
    check_for_hierarchy_violation();
    if (!internal_mutex.try_lock())  // 7
      return false;
    update_hierarchy_value();
    return true;
  }
};
thread_local unsigned long hierarchical_mutex::this_thread_hierarchy_value(
    ULONG_MAX);  // 8
````

### 3.2.6 std::unique_lock

```` cpp
class some_big_object;
void swap(some_big_object& lhs, some_big_object& rhs);
class X {
 private:
  some_big_object some_detail;
  std::mutex m;

 public:
  X(some_big_object const& sd) : some_detail(sd) {}
  friend void swap(X& lhs, X& rhs) {
    if (&lhs == &rhs)
      return;
    std::unique_lock<std::mutex> lock_a(lhs.m, std::defer_lock);  // 1
    std::unique_lock<std::mutex> lock_b(rhs.m, std::defer_lock);  // 1
    // std::defer_lock 留下未上锁的互斥量
    std::lock(lock_a, lock_b);  // 2 互斥量在这里上锁
    swap(lhs.some_detail, rhs.some_detail);
  }
};
````

### 3.2.7 不同域中互斥量的传递

```` cpp
std::unique_lock<std::mutex> get_lock()
{
  extern std::mutex some_mutex;
  std::unique_lock<std::mutex> lk(some_mutex);
  prepare_data();
  return lk; // 1
}
void process_data()
{
  std::unique_lock<std::mutex> lk(get_lock()); // 2
  do_something();
}
````

### 3.2.8 锁的粒度

可能的情况下，锁住互斥量的同时只能对共享数据进行访问，尽量不要试图对锁外数据进行处理。特别是做一些费时的动作

```` cpp
void get_and_process_data()
{
  std::unique_lock<std::mutex> my_lock(the_mutex);
  some_class data_to_process=get_next_data_chunk();
  my_lock.unlock(); // 1 不要让锁住的互斥量越过process()函数的调用
  result_type result=process(data_to_process);
  my_lock.lock(); // 2 为了写入数据，对互斥量再次上锁
  write_result(data_to_process,result);
}
````

不需要让锁住的互斥量越过对process()函数的调用，所以可以在函数调用前对互斥量进行手动解锁，之后对其再次上锁
锁不仅要能锁住合适粒度的数据，还要控制锁的持有时间，以及哪些操作在执行的同时能够拥有锁。一般情况下，尽可能将持有锁的时间缩减到最小

代码3.10 比较操作符中一次锁住一个互斥量

```` cpp
class Y {
 private:
  int some_detail;
  mutable std::mutex m;
  int get_detail() const {
    std::lock_guard<std::mutex> lock_a(m);  // 1
    return some_detail;
  }

 public:
  Y(int sd) : some_detail(sd) {}
  friend bool operator==(Y const& lhs, Y const& rhs) {
    if (&lhs == &rhs)
      return true;
    int const lhs_value = lhs.get_detail();  // 2
    int const rhs_value = rhs.get_detail();  // 3
    return lhs_value == rhs_value;           // 4
  }
};
````

代码3.10中，当操作符返回true时，就意味着在这个时间点上的lhs.some_detail与另一个时间点的rhs.some_detail相同。

这两个值在读取之后，可能会以任意方式修改。两个值会在2和3处进行交换，这样就会失去了比较的意义。

有时可能找不到一个合适的粒度级别，因为并不是所有对数据结构的访问都需要同一级的保护。**这个例子中，就需要寻找一个合适的机制，去替换 std::mutex**

## 3.3 保护共享数据的方式

互斥量是一种通用的机制，但其并非保护共享数据的唯一方式。有很多方式可以在特定情况下，对共享数据提供合适的保护。

### 3.3.1 保护共享数据的初始化过程（单例模式）

代码3.11 使用延迟初始化(线程安全)的过程

```` cpp
std::shared_ptr<some_resource> resource_ptr;
std::mutex resource_mutex;
void foo()
{
  std::unique_lock<std::mutex> lk(resource_mutex); // 所有线程在此序列化
  if(!resource_ptr)
  {
    resource_ptr.reset(new some_resource); // 只有初始化过程需要保护
  }
  lk.unlock();
  resource_ptr->do_something();
}
````

双检查锁

```` cpp
void undefined_behaviour_with_double_checked_locking()
{
  if(!resource_ptr) // 1
  {
    std::lock_guard<std::mutex> lk(resource_mutex);
    if(!resource_ptr) // 2
    {
    resource_ptr.reset(new some_resource); // 3
    }
  }
  resource_ptr->do_something(); // 4
}
````

因为有潜在的条件竞争。未被锁保护的读取操作①没有与其他线程里被锁保护的写入操作③进行同步，因此就会产生条件竞争，这个条件竞争不仅覆盖指针本身，还会影响到其指向的对象；**即使一个线程知道另一个线程完成对指针进行写入，它可能没有看到新创建的some_resource实例**，然后调用do_something()④后，得到不正确的结果。
<!-- https://www.aristeia.com/Papers/DDJ_Jul_Aug_2004_revised.pdf -->

std::once_flag 和 std::call_once

```` cpp
std::shared_ptr<some_resource> resource_ptr;
std::once_flag resource_flag; // 1
void init_resource()
{
  resource_ptr.reset(new some_resource);
}
void foo()
{
  std::call_once(resource_flag,init_resource); // 可以完整的进行一次初始化
  resource_ptr->do_something();
}
````

代码3.12 使用 std::call_once 实现类成员的延迟初始化(线程安全)

```` cpp
class X {
 private:
  connection_info connection_details;
  connection_handle connection;
  std::once_flag connection_init_flag;
  void open_connection() {
    connection = connection_manager.open(connection_details);
  }

 public:
  X(connection_info const& connection_details_)
      : connection_details(connection_details_) {}
  void send_data(data_packet const& data)  // 1
  {
    std::call_once(connection_init_flag, &X::open_connection, this);  // 2
    connection.send_data(data);
  }
  data_packet receive_data()  // 3
  {
    std::call_once(connection_init_flag, &X::open_connection, this);  // 2
    return connection.receive_data();
  }
};
````

**C++11标准中**，static 局部变量的初始化及定义完全在一个线程中发生，并且没有其他线程可在初始化完成前对其进行处理，条件竞争终止于初始化阶段
在只需要一个全局实例情况下，这里提供一个 std::call_once 的替代方案

```` cpp
class my_class;
my_class& get_my_class_instance()
{
  static my_class instance; // 线程安全的初始化过程
  return instance;
}
````

### 3.3.2 保护不常更新的数据结构

这里需要另一种不同的互斥量，这种互斥量常被称为“读者-作者锁”，因为其允许两种不同的使用方式：一个“作者”线程独占访问和共享访问，让多个“读者”线程并发访问。

C++17标准库提供了两种非常好的互斥量—— std::shared_mutex 和 std::shared_timed_mutex 。C++14只提供了 std::shared_timed_mutex

std::shared_timed_mutex 支持更多的操作方式(参考4.3节)， std::shared_mutex 有更高的性能优势，但支持的操作较少。

比起使用 std::mutex 实例进行同步，不如使用 std::shared_mutex 来做同步

对于更新操作，可以使用 std::lock_guard<std::shared_mutex> 和 std::unique_lock<std::shared_mutex> 上锁。作为 std::mutex 的替代方案，与 std::mutex 所做的一样，这就能保证更新线程的独占访问。那些无需修改数据结构的线程，可以使用 std::shared_lock<std::shared_mutex> 获取访问权。

代码3.13 使用 std::shared_mutex 对数据结构进行保护
  
```` cpp
#include <map>
#include <mutex>
#include <shared_mutex>
#include <string>
class dns_entry;
class dns_cache {
  std::map<std::string, dns_entry> entries;
  mutable std::shared_mutex entry_mutex;

 public:
  dns_entry find_entry(std::string const& domain) const {
    std::shared_lock<std::shared_mutex> lk(entry_mutex);  // 1
    std::map<std::string, dns_entry>::const_iterator const it =
        entries.find(domain);
    return (it == entries.end()) ? dns_entry() : it->second;
  }
  void update_or_add_entry(std::string const& domain,
                           dns_entry const& dns_details) {
    std::lock_guard<std::shared_mutex> lk(entry_mutex);  // 2
    entries[domain] = dns_details;
  }
};
````

### 3.3.3 嵌套锁

线程对已经获取的 std::mutex (已经上锁)再次上锁是错误的，尝试这样做会导致未定义行为。在某些情况下，一个线程会尝试在释放一个互斥量前多次获取。
因此，C++标准库提供了 std::recursive_mutex 类。除了可以在同一线程的单个实例上多次上锁，其他功能与 std::mutex 相同。
其他线程对互斥量上锁前，当前线程必须释放拥有的所有锁，所以如果你调用lock()三次，也必须调用unlock()三次。
嵌套锁一般用在可并发访问的类上，所以使用互斥量保护其成员数据。每个公共成员函数都会对互斥量上锁，然后完成对应的操作后再解锁互斥量。不过，有时成员函数会调用另一个成员函数，这种情况下，第二个成员函数也会试图锁住互斥量，这就会导致未定义行为的发生。“变通的”解决方案会将互斥量转为嵌套锁，第二个成员函数就能成功的进行上锁，并且函数能继续执行。
但是这种方式过于草率和不合理，所以不推荐这样的使用方式。特别是，对应类的不变量通常会被破坏。这意味着，当不变量被破坏时，第二个成员函数还需要继续执行。
一个比较好的方式是，从中提取出一个函数作为类的私有成员，这个私有成员函数不会对互斥量进行上锁(调用前必须获得锁)。
