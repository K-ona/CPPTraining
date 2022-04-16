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

C++17中的还提供了一种加强版数据保护机制—— std::scoped_lock
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

