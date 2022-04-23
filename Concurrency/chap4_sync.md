# 同步操作

本章将讨论如何使用条件变量等待事件，介绍future，锁存器( latches )和栅栏 ( barriers )，以及如何简化同步操作。

## 4.1 等待事件或条件

### 4.1.1 等待条件达成

C++标准库对条件变量有两套实现： std::condition_variable 和 std::condition_variable_any ，这两个实现都包含在 <condition_variable> 头文件的声明中。

两者都需要与互斥量一起才能工作(互斥量是为了同步)，前者仅能与 std::mutex 一起工作，而后者可以和合适的互斥量一起工作，从而加上了 _any 的后缀。

因为 std::condition_variable_any 更加通用，不过在性能和系统资源的使用方面会有更多的开销，所以通常会将 std::condition_variable 作为首选类型。当对灵活性有要求时，才会考虑 std::condition_variable_any

代码4.1 使用 std::condition_variable 处理数据等待

```` cpp
std::mutex mut;
std::queue<data_chunk> data_queue;  // 1
std::condition_variable data_cond;

void data_preparation_thread() {
  while (more_data_to_prepare()) {
    data_chunk const data = prepare_data();
    std::lock_guard<std::mutex> lk(mut);
    data_queue.push(data);   // 2
    data_cond.notify_one();  // 3
  }
}

void data_processing_thread() {
  while (true) {
    std::unique_lock<std::mutex> lk(mut);                    // 4
    data_cond.wait(lk, [] { return !data_queue.empty(); });  // 5
    data_chunk data = data_queue.front();
    data_queue.pop();
    lk.unlock();  // 6
    process(data);
    if (is_last_chunk(data))
      break;
  }
}
````

wait()会去检查这些条件(通过Lambda函数)，当条件满足(Lambda函数返回true)时返回。如果条件不满足(Lambda函数返回false)，wait()将解锁互斥量，并且将线程(处理数据的线程)置于阻塞或等待状态。当准备数据的线程调用notify_one()通知条件变量时，处理数据的线程从睡眠中苏醒，重新获取互斥锁，并且再次进行条件检查。在条件满足的情况下，从wait()返回并继续持有锁。当条件不满足时，线程将对互斥量解锁，并重新等待。

这就是为什么用 std::unique_lock 而不使用 std::lock_guard 的原因——等待中的线程必须在等待期间解锁互斥量，并对互斥量再次上锁，而 std::lock_guard 没有这么灵活。如果互斥量在线程休眠期间保持锁住状态，准备数据的线程将无法锁住互斥量，也无法添加数据到队列中。同样，等待线程也永远不会知道条件何时满足。

调用wait()的过程中，在互斥量锁定时，可能会去检查条件变量若干次，当提供测试条件的函数返回true就会立即返回。当等待线程重新获取互斥量并检查条件变量时，并非直接响应另一个线程的通知，就是所谓的**伪唤醒(spurious wakeup)**:

使用队列在多个线程中转移数据(如代码4.1)很常见。做得好的话，同步操作可以在队列内部完成，这样同步问题和条件竞争出现的概率也会降低。鉴于这些好处，需要从代码4.1中提取出一个通用线程安全的队列。

代码4.2 std::queue 接口

```` cpp
template <class T, class Container = std::deque<T> >
class queue {
 public:
  explicit queue(const Container&);
  explicit queue(Container&& = Container());
  template <class Alloc>
  explicit queue(const Alloc&);
  template <class Alloc>
  queue(const Container&, const Alloc&);
  template <class Alloc>
  queue(Container&&, const Alloc&);
  template <class Alloc>
  queue(queue&&, const Alloc&);


  void swap(queue& q);

  bool empty() const;
  size_type size() const;
  T& front();
  const T& front() const;
  T& back();
  const T& back() const;

  void push(const T& x);
  void push(T&& x);
  void pop();

  template <class... Args>
  void emplace(Args&&... args);
};
````

代码4.3 线程安全队列的接口

```` cpp
#include <memory>  // 为了使用std::shared_ptr
template <typename T>
class threadsafe_queue {
 public:
  threadsafe_queue();
  threadsafe_queue(const threadsafe_queue&);
  threadsafe_queue& operator=(const threadsafe_queue&) =
      delete;  // 不允许简单的赋值
  void push(T new_value);
  bool try_pop(T& value);        // 1
  std::shared_ptr<T> try_pop();  // 2
  void wait_and_pop(T& value);
  std::shared_ptr<T> wait_and_pop();
  bool empty() const;
};
````

代码4.4 从代码4.1中提取push()和wait_and_pop()

```` cpp
#include <condition_variable>
#include <mutex>
#include <queue>
template <typename T>
class threadsafe_queue {
 private:
  std::mutex mut;
  std::queue<T> data_queue;
  std::condition_variable data_cond;

 public:
  void push(T new_value) {
    std::lock_guard<std::mutex> lk(mut);
    data_queue.push(new_value);
    data_cond.notify_one();
  }

  void wait_and_pop(T& value) {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this] { return !data_queue.empty(); });
    value = data_queue.front();
    data_queue.pop();
  }
};

threadsafe_queue<data_chunk> data_queue;  // 1

void data_preparation_thread() {
  while (more_data_to_prepare()) {
    data_chunk const data = prepare_data();
    data_queue.push(data);  // 2
  }
}

void data_processing_thread() {
  while (true) {
    data_chunk data;
    data_queue.wait_and_pop(data);  // 3
    process(data);
    if (is_last_chunk(data))
      break;
  }
}
````

代码4.5 使用条件变量的线程安全队列(完整版)
  
```` cpp
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
template <typename T>
class threadsafe_queue {
 private:
  mutable std::mutex mut;  // 1 互斥量必须是可变的
  std::queue<T> data_queue;
  std::condition_variable data_cond;

 public:
  threadsafe_queue() {}
  threadsafe_queue(threadsafe_queue const& other) {
    std::lock_guard<std::mutex> lk(other.mut);
    data_queue = other.data_queue;
  }

  void push(T new_value) {
    std::lock_guard<std::mutex> lk(mut);
    data_queue.push(new_value);
    data_cond.notify_one();
  }

  void wait_and_pop(T& value) {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this] { return !data_queue.empty(); });
    value = data_queue.front();
    data_queue.pop();
  }

  std::shared_ptr<T> wait_and_pop() {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this] { return !data_queue.empty(); });
    std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
    data_queue.pop();
    return res;
  }

  bool try_pop(T& value) {
    std::lock_guard<std::mutex> lk(mut);
    if (data_queue.empty())
      return false;
    value = data_queue.front();
    data_queue.pop();
    return true;
  }

  std::shared_ptr<T> try_pop() {
    std::lock_guard<std::mutex> lk(mut);
    if (data_queue.empty())
      return std::shared_ptr<T>();
    std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
    data_queue.pop();
    return res;
  }

  bool empty() const {
    std::lock_guard<std::mutex> lk(mut);
    return data_queue.empty();
  }
};
````

## 4.2 使用future

C++标准库中有两种future，声明在 <future> 头文件中: unique future( std::future<> )和shared futures( std::shared_future<> )，与了 std::unique_ptr 和 std::shared_ptr 非常类似。 std::future 只能与指定事件相关联，而 std::shared_future 就能关联多个事件。

后者的实现中，所有实例会在同时变为就绪状态，并且可以访问与事件相关的数据。这种关联与模板有关，比如 std::unique_ptr 和 std::shared_ptr 的模板参数就是相关的数据类型。与数据无关处的，可以使用 std::future<void> 与 std::shared_future<void> 的特化模板。

最简单的事件，就是在后台运行的计算操作。第2章中已经清楚了 std::thread 执行的任务不能有返回值，不过这个问题能使用future进行解决。

### 4.2.1 后台任务的返回值

假设有一个需要长时间的运算，需要计算出一个有效值，但并不迫切需要这个值。你可以启动新线程来执行这个计算，你需要计算的结果，而 std::thread 并不提供直接接收返回值的机制。这里就需要 **std::async 函数模板** (也是在头文件 <future> )。

当不着急让任务结果时，可以使用 std::async 启动一个**异步任务**。与 std::thread 对象等待的方式不同， **std::async 会返回一个 std::future 对象**，这个对象持有最终计算出来的结果。当需要这个值时，只需要调用这个对象的get()成员函数，就会阻塞线程直到future为就绪为止，并返回计算结果。

代码4.6 std::future 从异步任务中获取返回值

```` cpp
#include <future>
#include <iostream>

int find_the_answer_to_ltuae();
void do_other_stuff();

int main() {
  std::future<int> the_answer = std::async(find_the_answer_to_ltuae);
  do_other_stuff();
  std::cout << "The answer is " << the_answer.get() << std::endl;
}
````

代码4.7 使用 std::async 向函数传递参数

```` cpp
#include <future>
#include <string>

struct X {
  void foo(int, std::string const&);
  std::string bar(std::string const&);
};

struct Y {
  double operator()(double);
};

class move_only {
 public:
  move_only();
  move_only(move_only&&);
  move_only(move_only const&) = delete;
  move_only& operator=(move_only&&);
  move_only& operator=(move_only const&) = delete;
  void operator()();
};

int main() {
  X x;
  auto f1 = std::async(&X::foo, &x, 42,
                       "hello");  // 调用p->foo(42, "hello")，p是指向x的指针
  auto f2 =
      std::async(&X::bar, x,
                 "goodbye");  // 调用tmpx.bar("goodbye")， tmpx是x的拷贝副本
  Y y;
  auto f3 =
      std::async(Y(), 3.141);  // 调用tmpy(3.141)，tmpy通过Y的移动构造函数得到
  auto f4 = std::async(std::ref(y), 2.718);  // 调用y(2.718)
  X baz(X&);

  std::async(baz, std::ref(x));  // 调用baz(x)

  auto f5 = std::async(
      move_only());  // 调用tmp()，tmp是通过std::move(move_only())构造得到
}
````

future的等待取决于 std::async 是否启动一个线程，或是否有任务在进行同步。

大多数情况下，也可以在函数调用之前向 std::async 传递一个额外参数，**这个参数的类型是 std::launch**，可以是 **std::launch::defered** ，表明函数调用延迟到wait()或get()函数调用时才执行(在调用线程中运行)， **std::launch::async** 表明函数必须在其所在的独立线程上执行，
**std::launch::deferred | std::launch::async** 表明实现可以选择这两种方式的一种。最后一个选项是默认的，当函数调用延迟，就可能不会再运行了。

**std::launch::async:** the task is executed on a different thread, potentially by launching a new thread
**std::launch::deferred:** the task is executed on the calling thread the first time its result is requested (lazy evaluation)

[cppreferences](https://en.cppreference.com/w/cpp/thread/async)

如下所示：

```` cpp
auto f6 = std::async(std::launch::async, Y(), 1.2); // 在新线程上执行
auto f7 = std::async(std::launch::deferred, baz, std::ref(x)); // 在 wait()或 get()调用时执行
auto f8 = std::async(
            std::launch::deferred | std::launch::async,
            baz, std::ref(x)); // 实现选择执行方式
auto f9 = std::async(baz, std::ref(x));
f7.wait(); // 调用延迟函数
````

使用 std::async 会将算法分割到各个任务中，这样程序就能并发了。

不过，这不是让 std::future 与任务实例相关联的唯一方式，也可以将任务包装入 std::packaged_task<> 中，或通过编写代码的方式，使用std::promise<> 模板显式设置值。

与 std::promise<> 相比， std::packaged_task<> 具有更高的抽象，所以我们从“高抽象”模板说起。

### 4.2.2 future与任务关联

**std::packaged_task<>** 会将future与函数或可调用对象进行绑定。当调用 **std::packaged_task<> 对象**时，就会调用相关函数或可调用对象，当future状态为就绪时，会存储返回值。

std::packaged_task<> 的模板参数是一个**函数签名**，比如void()就是一个没有参数也没有返回值的函数，或int(std::string&, double*) 就是有一个非const引用的 std::string 参数和一个指向double类型的指针参数，并且返回类型是int。

构造 std::packaged_task<> 实例时，必须传入函数或可调用对象。这个函数或可调用的对象，需要能接收指定的参数和返回(可转换为指定返回类型的)值。类型可以不完全匹配，因为这里类型可以隐式转换，可以用int类型参数和返回float类型的函数，来构建 std::packaged_task<double(double)> 实例。

函数签名的返回类型可以用来标识从get_future()返回的 std::future<> 的类型，而函数签名的参数列表，可用来指定packaged_task的函数调用操作符。

代码4.8 std::packaged_task<> 的偏特化
  
````cpp
template<>
class packaged_task<std::string(std::vector<char>*,int)>
{
 public:
  template<typename Callable>
  explicit packaged_task(Callable&& f);
  std::future<std::string> get_future();
  void operator()(std::vector<char>*,int);
};
````

std::packaged_task 是个可调用对象，可以封装在 std::function 对象中，从而作为线程函数传递到 std::thread 对象中，或作为可调用对象传递到另一个函数中或直接调用。

当 std::packaged_task 作为函数调用时，实参将由函数调用操作符传递至底层函数，并且返回值作为异步结果存储在 std::future 中，可通过get_future()获取。

因此可以用 std::packaged_task 对任务进行打包，并适时的取回future。当异步任务需要返回值时，可以等待future状态变为“就绪”

**线程间传递任务**

代码4.9 使用 std::packaged_task 执行一个图形界面线程

```` cpp
#include <deque>
#include <future>
#include <mutex>
#include <thread>
#include <utility>
std::mutex m;
std::deque<std::packaged_task<void()> > tasks;
bool gui_shutdown_message_received();
void get_and_process_gui_message();

void gui_thread()  // 1
{
  while (!gui_shutdown_message_received())  // 2
  {
    get_and_process_gui_message();  // 3
    std::packaged_task<void()> task;
    {
      std::lock_guard<std::mutex> lk(m);
      if (tasks.empty())  // 4
        continue;
      task = std::move(tasks.front());  // 5
      tasks.pop_front();
    }
    task();  // 6
  }
}

std::thread gui_bg_thread(gui_thread);
template <typename Func>
std::future<void> post_task_for_gui_thread(Func f) {
  std::packaged_task<void()> task(f);         // 7
  std::future<void> res = task.get_future();  // 8
  std::lock_guard<std::mutex> lk(m);
  tasks.push_back(std::move(task));  // 9
  return res;                        // 10
}
````

例子中使用 std::packaged_task<void()> 创建任务，其中包含了一个无参数无返回值的函数或可调用对象(如果当这个调用有返回值时，返回值会被丢弃)。

这可能是最简单的任务， std::packaged_task 也可以用于复杂的情况——通过指定不同的函数签名作为模板参数，不仅可以改变其返回类型(因此该类型的数据会存在期望相关的状态中)，也可以改变函数操作符的参数类型。

这个例子可以简单的扩展成允许任务运行在图形界面线程上，并且接受传参，还可以通过 std::future 获取返回值。

### 4.2.3 使用std::promises

**std::promise<T>** 提供设定值的方式(类型为T)，这个类型会和后面看到的 std::future<T> 对象相关联。 std::promise/std::future 对提供一种机制：future可以阻塞等待线程，提供数据的线程可以使用promise对相关值进行设置，并将future的状态置为“就绪”。

代码4.10中是单线程处理多连接的实现，这个例子中，可以使用一对 std::promise<bool>/std::future<bool> 找出传出成功的数据块，与future相关的只是简单的“成功/失败”标识。

对于传入包，与future相关的数据就是数据包的有效负载。

代码4.10 使用promise解决单线程多连接问题

```` cpp
#include <future>
void process_connections(connection_set& connections) {
  while (!done(connections))  // 1
  {
    for (connection_iterator  // 2
             connection = connections.begin(),
             end = connections.end();
         connection != end; ++connection) {
      if (connection->has_incoming_data())  // 3
      {
        data_packet data = connection->incoming();
        std::promise<payload_type>& p = connection->get_promise(data.id);  // 4
        p.set_value(data.payload);
      }
      if (connection->has_outgoing_data())  // 5
      {
        outgoing_packet data = connection->top_of_outgoing_queue();
        connection->send(data.payload);
        data.promise.set_value(true);  // 6
      }
    }
  }
}
````

上面的代码不理会异常，一切工作都会很好的执行，但有悖常理。有时候磁盘满载，有时候会找不到东西，有时候网络会断，还有时候数据库会崩溃。当需要某个操作的结果时，就需要在对应的线程上执行这个操作，因为代码可以通过异常来报告错误。不过，这会对使用 std::packaged_task 或 std::promise 带来一些不必要的限制。因此，C++标准库提供了一种在以上情况下清理异常的方法，并且允许将异常存储为相关结果的一部分。

### 4.2.4 将异常存于future中

函数作为 std::async 的一部分时，当调用抛出一个异常时，这个异常就会存储到future中，之后future的状态置为“就绪”，之后调用get()会抛出已存储的异常(注意：标准级别没有指定重新抛出的这个异常是原始的异常对象，还是一个拷贝。不同的编译器和库将会在这方面做出不同的选择)。将函数打包入 std::packaged_task 任务包后，当任务调用时，同样的事情也会发生。打包函数抛出一个异常，这个异常将存储在future中，在get()调用时会再次抛出。

当然，通过函数的显式调用， std::promise 也能提供同样的功能。当存入的是异常而非数值时，就需要调用set_exception()成员函数，而非set_value()。这通常是用在一个catch块中，并作为算法的一部分。为了捕获异常，这里使用异常填充promise

```` cpp
extern std::promise<double> some_promise;
try
{
  some_promise.set_value(calculate_value());
}
catch(...)
{
  some_promise.set_exception(std::current_exception());
}
````

另一种向future中存储异常的方式，在没有调用promise上的任何设置函数前，或正在调用包装好的任务时，销毁与 std::promise 或 std::packaged_task 相关的future对象。任何情况下，当future的状态还不是“就绪”时，调用 std::promise 或 std::packaged_task 的析构函数，将会存储一个与 std::future_errc::broken_promise 错误状态相关的 std::future_error 异常。通过创建一个future，可以构造一个promise为其提供值或异常，也可以通过销毁值和异常源，去违背promise。这种情况下，编译器没有在future中存储任何东西，线程可能会永远的等下去。

很多线程在等待的时候，只有一个线程能获取结果。当多个线程等待相同事件的结果时，就需要使用 std::shared_future 来替代 std::future 了

### 4.2.5 多个线程的等待

多线程在没有额外同步的情况下，访问独立 ```std::future``` 对象时，就会有数据竞争和未定义行为。因为 ```std::future``` 独享同步结果，并且通过调用```get()```函数，**数据获取操作的一次性**，这就让并发访问变的毫无意义。

```std::future``` 是只移动的，所以其所有权可以在不同的实例中互相传递，但只有一个实例可以获得特定的同步结果，而 ```std::shared_future``` 实例是可拷贝的，所以多个对象可以引用同一关联期望值的结果。

```std::shared_future``` 的实例同步 ```std::future``` 实例的状态。当 ```std::future``` 对象没有与其他对象共享同步状态所有权，那么所有权必须使用 ```std::move``` 将所有权传递到 ```std::shared_future``` ，其默认构造函数如下
  
```` cpp
std::promise<int> p;
std::future<int> f(p.get_future());
assert(f.valid()); // 1 期望值 f 是合法的
std::shared_future<int> sf(std::move(f));
assert(!f.valid()); // 2 期望值 f 现在是不合法的
assert(sf.valid()); // 3 sf 现在是合法的
````

std::future 有一个share()成员函数，可用来创建新的 std::shared_future，并且可以直接转移future的所有权。

```` cpp
std::promise< std::map< SomeIndexType, SomeDataType, SomeComparator,
SomeAllocator>::iterator> p;
auto sf=p.get_future().share();
````

## 4.3 限时等待

这里介绍两种指定超时方式：一种是“时间段”，另一种是“时间点”。第一种方式，需要指定一段时间(例如，30毫秒)。第二种方式，就是指定一个时间点(例如，世界标准时间[UTC]17:30:15.045987023，2011年11月30日)。多数等待函数提供变量，对两种超时方式进行处理。处理持续时间的变量以 _for 作为后缀，处理绝对时间的变量以 until 作为后缀

所以， ```std::condition_variable``` 的两个成员函数```wait_for()```和```wait_until()```成员函数分别有两个重载，这两个重载都与wait()成员函数的重载相关——其中一个只是等待信号触发，或超期，亦或伪唤醒，并且醒来时会使用谓词检查锁，并且只有在校验为true时才会返回(这时条件变量的条件达成)，或直接超时。

### 4.3.1 时钟

时钟节拍被指定为1/x(x在不同硬件上有不同的值)秒，这是由时间周期所决定——若一个时钟一秒有25个节拍，则一个周期为 ```std::ratio<1, 25>``` ，当一个时钟的时钟节拍每2.5秒一次，周期就可以表示为 ```std::ratio<5,2>```

当时钟节拍均匀分布(无论是否与周期匹配)，并且不可修改，这种时钟就称为稳定时钟。is_steady静态数据成员为true时，也表明这个时钟就是稳定的

稳定闹钟对于计算超时很重要，所以C++标准库提供一个稳定时钟 ```std::chrono::steady_clock```，
C++标准库提供的其他时钟可表示为 ```std::chrono::system_clock``` ，代表了系统时钟的“实际时间”，并且提供了函数，可将时间点转化为time_t类型的值
```std::chrono::high_resolution_clock```可能是标准库中提供的具有最小节拍周期(因此具有最高的精度)的时钟。

### 4.3.2 时间段

```std::chrono::duration<>``` 函数模板能够对时间段进行处理(线程库使用到的所有C++时间处理工具，都在 ```std::chrono``` 命名空间内)。第一个模板参数是一个类型表示(比如，int，long或double)，第二个模板参数是定制部分，表示每一个单元所用秒数。

例如，当几分钟的时间要存在short类型中时，可以写成 ``` std::chrono::duration<short, std::ratio<60, 1>> ``` ，因为60秒是才是1分钟，所以第二个参数写成 std::ratio<60, 1> 。当需要将毫秒级计数存在double类型中时，可以写成``` std::chrono::duration<double,std::ratio<1, 1000>> ```，因为1秒等于1000毫秒

标准库在 ```std::chrono``` 命名空间内为时间段变量提供一系列预定义类型：```nanoseconds[纳秒] ,
microseconds[微秒] , milliseconds[毫秒] , seconds[秒] , minutes[分]和hours[时]等```

方便起见，C++14中 std::chrono_literals 命名空间中有许多预定义的后缀操作符用来表示时长。下面的代码就是使用硬编码的方式赋予变量具体的时长：

```` cpp
using namespace std::chrono_literals;
auto one_day=24h;
auto half_an_hour=30min;
auto max_time_between_messages=30ms;
````

使用整型字面符时，```15ns```和 ```std::chrono::nanoseconds(15)``` 就是等价的。
当使用浮点字面量时，且未指明表示类型时，数值上会对浮点时长进行适当的缩放 (通常放大)。因此，```2.5min```会被表示为 ```std::chrono::duration<somefloating-point-type,std::ratio<60,1>>```

如果非常关心所选的浮点类型表示的范围或精度，就需要构造相应的对象来保证表示范围或精度

```` cpp
auto z = 2.5ms; // std::chrono::duration<long double, std::milli> z
auto z1 = std::chrono::duration<double, std::milli>(2.5); 
````

当不要求截断值的情况下(时转换成秒是没问题，但是秒转换成时就不行)时间段的转换是隐式的，显示强制转换可以由 ```std::chrono::duration_cast<>``` 来完成。
  
```` cpp
std::chrono::milliseconds ms(54802);
std::chrono::seconds s=
std::chrono::duration_cast<std::chrono::seconds>(ms); // s == 54
````

时间值支持四则运算，所以能够对两个时间段进行加减，或者是对一个时间段乘除一个常数(模板的第一个参数)来获得一个新时间段变量。例如，```5*seconds(1)```与```seconds(5)```或```minutes(1)-seconds(55)```是一样。

在时间段中可以通过count()成员函数获得单位时间的数量。例如， ```std::chrono::milliseconds(1234).count()``` 就是1234

基于时间段的等待可由 ```std::chrono::duration<>``` 来完成。
例如：等待future状态变为就绪需要35毫秒：

```` cpp
std::future<int> f=std::async(some_task);
if(f.wait_for(std::chrono::milliseconds(35)) == std::future_status::ready)
do_something_with(f.get());
````

等待future时，超时时会返回 ```std::future_status::timeout``` 。当future状态改变，则会返回 ```std::future_status::ready``` 。当与future相关的任务延迟了(如 ```std::async```使用```std::launch::deferred```)，则会返回 ```std::future_status::deferred```

当然，系统调度的不确定性和不同操作系统的时钟精度意味着：线程调用和返回的实际时间间隔可能要比35毫秒长。

### 4.3.3 时间点

时间点可用 ```std::chrono::time_point<>``` 来表示，第一个参数用来指定使用的时钟，第二个函数参数用来表示时间单位(特化的 ```std::chrono::duration<>``` )

而时间戳是时钟的基本属性，不可以直接查询，其在C++标准中已经指定。通常，UNIX时间戳表示1970年1月1日 00:00。

当两个时钟共享一个时间戳时，其中一个time_point类型可以与另一个时钟类型中的time_point相关联。虽然不知道UNIX时间戳的具体值，但可以通过对指定time_point类型使用time_since_epoch()来获取时间戳，该成员函数会返回一个数值，这个数值是指定时间点与UNIX时间戳的时间间隔。

例如，指定一个时间点 ```std::chrono::time_point<std::chrono::system_clock, std::chrono::minutes>```，这就与系统时钟有关，且实际中的一分钟与系统时钟精度应该不相同(通常差几秒)

可以通过对 ```std::chrono::time_point<>``` 实例进行加/减，来获得一个新的时间点，所以 ```std::chrono::high_resolution_clock::now() + std::chrono::nanoseconds(500)``` 将得到500纳秒后的时间，这对于计算绝对时间来说非常方便。

也可以减去一个时间点(二者需要共享同一个时钟)，结果是两个时间点的时间差。这对于代码块的计时是很有用的，

例如：计算do_something()执行时间，可以这样写：

```` cpp
auto start=std::chrono::high_resolution_clock::now();
do_something();
auto stop = std::chrono::high_resolution_clock::now();
std::cout << "do_something() took "
<< std::chrono::duration<double, std::chrono::seconds>(stop-start).count()
<<" seconds" <<std::endl;
````

可以使用 std::chrono::system_clock::to_time_point() 静态成员函数，对时间点进行操作。

代码4.11 等待条件变量满足条件——有超时功能

```` cpp
#include <chrono>
#include <condition_variable>
#include <mutex>
std::condition_variable cv;
bool done;
std::mutex m;
bool wait_loop() {
  auto const timeout =
      std::chrono::steady_clock::now() + std::chrono::milliseconds(500);
  std::unique_lock<std::mutex> lk(m);
  while (!done) {
    if (cv.wait_until(lk, timeout) == std::cv_status::timeout)
      break;
  }
  return done;
}
````

condition_variable.wait_until 的返回值为 ```std::cv_status::timeout``` 或 ```std::cv_status::no_timeout```

### 4.3.2 使用超时

线程使用的两个处理函数分别是 ```std::this_thread::sleep_for()``` 和 ```std::this_thread::sleep_until()```。
它们的工作就像一个简单的闹钟：当线程因为指定时长而进入睡眠时，可使用sleep_for()唤醒，指定休眠的时间点之后，可使用sleep_until唤醒。

休眠只是超时处理的一种形式，超时可以配合条件变量和future一起使用。超时甚至可以在获取互斥锁时(当互斥量支持超时时)使用。

std::timed_mutex 和 std::recursive_timed_mutex 支持超时。这两种类型也有try_lock_for()和try_lock_until()成员函数

总结如下表

参数列表为“延时”(duration)必须是 std::duration<> 的实例，并且列出为时间点(time_point)必须是 std::time_point<> 的实例。

![可接受超时的函数](..\src\img\可接受超时的函数.png)

## 4.4 简化代码

### 4.4.1 使用future的函数化编程（functional programming）

函数化编程的好处并不限于将“纯粹”作为默认方式(范型)的语言。C++是一个多范型的语言，也可以写出FP类型的程序。C++11的方式要比C++98简单许多，因为C++11支持Lambda表达式(详见附录A，A.6节)，还加入了Boost和TR1中的 std::bind ，以及自动可以自行推断类型的自动变量(详见附录A，A.7节)。future作为最后一块拼图，使得函数化编程模式并发化(FP-style concurrency)在C++中成为可能。future可以在线程间互相传递，并允许计算结果互相依赖

**快速排序——FP模式版**

代码4.12 快速排序——串行版

```` cpp
template <typename T>
std::list<T> sequential_quick_sort(std::list<T> input) {
  if (input.empty()) {
    return input;
  }
  std::list<T> result;
  result.splice(result.begin(), input, input.begin());  // 1
  T const& pivot = *result.begin();                     // 2
  auto divide_point = std::partition(
      input.begin(), input.end(), [&](T const& t) { return t < pivot; });  // 3
  std::list<T> lower_part;
  lower_part.splice(lower_part.end(), input, input.begin(),
                    divide_point);                               // 4
  auto new_lower(sequential_quick_sort(std::move(lower_part)));  // 5
  auto new_higher(sequential_quick_sort(std::move(input)));      // 6
  result.splice(result.end(), new_higher);                       // 7
  result.splice(result.begin(), new_lower);                      // 8
  return result;
}
````

代码4.13 快速排序——并行版

```` cpp
#include <list>
#include <iostream>
#include <future>

template <typename T>
std::list<T> parallel_quick_sort(std::list<T> input) {
  if (input.empty()) {
    return input;
  }
  std::list<T> result;
  result.splice(result.begin(), input, input.begin());
  T const& pivot = *result.begin();
  auto divide_point = std::partition(input.begin(), input.end(),
                                     [&](T const& t) { return t < pivot; });
  std::list<T> lower_part;
  lower_part.splice(lower_part.end(), input, input.begin(), divide_point);
  std::future<std::list<T>> new_lower(  // 1
      std::async(&parallel_quick_sort<T>, std::move(lower_part)));
  auto new_higher(parallel_quick_sort(std::move(input)));  // 2
  result.splice(result.end(), new_higher);                 // 3
  result.splice(result.begin(), new_lower.get());          // 4
  return result;
}
````

```std::async()``` 会启动一个新线程，这样当递归三次时，就会有八个线程在运行了。当递归十次(对于大约有1000个元素的列表)，如果硬件能处理这十次递归调用，将会创建1024个执行线程。当运行库认为产生了太多的任务时(也许是因为数量超过了硬件并发的最大值)，可能会同步的切换新产生的任务。**当任务过多时(已影响性能)，为了避免任务传递的开销，这些任务应该在使用get()获取结果的线程上运行，而不是在新线程上运行**

[Use async() to spawn concurrent tasks](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#cp61-use-async-to-spawn-concurrent-tasks)

比起使用 ```std::async()``` ，可以写一个```spawn_task()```函数对 ```std::packaged_task``` 和 ```std::thread``` 做一下包装。如代码4.14中所示，需要为函数结果创建一个 ```std::packaged_task``` 对象， 并从这个对象中获取future，或在线程中返回future

其本身并没有太多优势(事实上会造成大规模的超额任务)，但可为转型成一个更复杂的实现进行铺垫，实现会向队列添加任务，而后使用线程池的方式来运行。```std::async``` 更适合于已知所有任务的情况，并且要能完全控制线程池中构建或执行过任务的线程。

代码4.14 spawn_task的简单实现

```` cpp
template <typename F, typename A>
std::future<typename std::result_of<F(A&&)>::type> spawn_task(F&& f, A&& a) {
  typedef typename std::result_of<F(A &&)>::type result_type;
  std::packaged_task<result_type(A&&)>
  task(std::move(f)); 
  std::future<result_type> res(task.get_future()); 
  std::thread t(std::move(task), std::move(a)); 
  t.detach(); 
  return res; 
}
````

函数化编程可算作是并发编程的范型，并且也是通讯顺序进程(**CSP，Communicating Sequential Processes**)的范型，这里的线程没有共享数据，但有通讯通道允许信息在不同线程间进行传递。

### 4.4.2 使用消息传递的同步操作

CSP的概念很简单：没有共享数据时，每个线程可以基于所接收到的信息独立运行。每个线程都是一个状态机：当收到一条信息，会以某种方式更新状态，并且可能向其他线程发出信息(消息处理机制依赖于线程的初始化状态)。这是有限状态机模式的实现，并且状态机可以隐式实现，这种方式更加依赖于明确的行为要求和专业的编程团队。无论选用哪种方式去实现线程，任务都会进行独立处理，消除潜在的混乱(数据共享并发)，就让编程变的更加简单。

这种程序设计的方式被称为 **[参与者模式(Actor model)](https://en.wikipedia.org/wiki/Actor_model)**——在系统中有很多独立的(运行在一个独立的线程上)参与者，这些参与者会互相发送信息，去执行手头上的任务，并且不会共享状态，除非是通过信息直接传入的。

为了响应它接收到的消息，参与者可以：做出本地决策，创建更多参与者，发送更多消息，并确定如何响应收到的下一条消息。 Actor 可以修改自己的私有状态，但**只能通过消息传递间接影响彼此（无需基于锁的同步）**

一个并发系统中，这种编程方式可以极大的简化任务的设计，因为每一个线程都完全被独立对待。因此，使用多线程去分离关注点时，需要明确线程之间的任务应该如何分配。

### 4.4.3 扩展规范中的持续性并发

并发技术扩展规范在 ```std::experiment``` 命名空间中提供了新的类型 ```std::promise``` 和 ```std::packaged_taks``` 与 std 命名空间中类型完全不同，其返回实例类型为 ```std::experimental::future``` ，而不是 ```std::future``` 这能让使用者体会 ```std::experimental::future``` 所带来的新特性——**持续性**

假设任务产生了一个结果，并且future持有这个结果。然后，需要写一些代码来处理这个结果。使用 ```std::future``` 时，必须等待future的状态变为就绪态，不然就使用全阻塞函数```wait()```，或是使用```wait_for()/wait_unitl()```成员函数进行等待，而这会让代码变得非常复杂。用一句话来说“完事俱备，只等数据”，这也就是持续性的意义。为了给future添加持续性，只需要在成员函数后添加then()即可。比如：给定一个```future fut```，添加持续性的调用即为 ```fut.then(continuation_function)```

与直接调用 std::async 或 std::thread 不同，持续性函数不需要传入参数，因为运行库已经为其定义好了参数——会传入处于就绪态的future，这个future保存了持续性触发后的结果

**this* 关联的共享状态就绪时，将在 **未指定的执行线程上调用延续**(continuation) INVOKE(std::move(fd), std::move(*this))，其中 INVOKE 是 continuation_function 中定义的可调用操作.

从延续返回的任何值都作为结果存储在返回的 future 对象的共享状态中, 从延续执行传播的任何异常都作为异常结果存储在返回的 future 对象的共享状态中。

代码4.17 使用并发技术扩展规范中的特性，实现与 std::async 等价的功能

```` cpp
template <typename Func>
std::experimental::future<decltype(std::declval<Func>()())> 
spawn_async (Func&& func) {
  std::experimental::promise<decltype(std::declval<Func>()())> p;
  auto res = p.get_future();
  std::thread t([p = std::move(p), f = std::decay_t<Func>(func)]() mutable {
    try {
      p.set_value_at_thread_exit(f());
    } catch (...) {
      p.set_exception_at_thread_exit(std::current_exception());
    }
  });
  t.detach();
  return res;
}
````

和 ```std::aync``` 一样，这里将函数的结果存储在future中，或捕获函数抛出的异常，将异常存到future中。

为了保证在future达到就绪态时，需要保证thread_local变量已经使用```set_value_at_thread_exit```和```set_exception_at_thread_exit```清理过了。

值是从then()调用中返回，其返回的future是完整的future。也就意味着，持续性可以进行连接

### 4.4.4 持续性连接

假设有一系列耗时任务要完成，并且要使用异步多线程完成这些任务，从而减轻主线程的计算压力，例如：用户登录应用时，需要将登录凭证发送给后台，在对身份信息进行验证后，从后台获取用户的账户信息，使用获取到的信息对显示进行更新

代码4.18 处理用户登录——同步方式

```` cpp
void process_login(std::string const& username, std::string const& password)
{
  try{
    user_id const id = backend.authenticate_user(username, password);
    user_data const info_to_display = backend.request_current_info(id);
    update_display(info_to_display);
  } catch(std::exception& e){
    display_error(e);
  }
}
````

代码4.19 处理用户登录——异步方式

```` cpp
std::future<void> process_login(std::string const& username,
                                std::string const& password) {
  return std::async(std::launch::async, [=]() {
    try {
      user_id const id = backend.authenticate_user(username, password);
      user_data const info_to_display = backend.request_current_info(id);
      update_display(info_to_display);
    } catch (std::exception& e) {
      display_error(e);
    }
  });
}
````

为了避免线程阻塞，机制需要对每个完成的任务进行连接：**持续性**
但这次将整个任务分成了一系列任务，并且每个任务在完成时回连到前一个任务上

代码4.20 处理用户登录——持续性方式

```` cpp
std::experimental::future<void> process_login(std::string const& username,
                                              std::string const& password) {
  return spawn_async(
             [=]() { return backend.authenticate_user(username, password); })
      .then([](std::experimental::future<user_id> id) {
        return backend.request_current_info(id.get());
      })
      .then([](std::experimental::future<user_data> info_to_display) {
        try {
          update_display(info_to_display.get());
        } catch (std::exception& e) {
          display_error(e);
        }
      });
}
````

每个持续性函数都以 ```std::experimental::future``` 作为独立参数，然后使用 ```.get()``` 来获取其拥有的值。这意味着异常会沿着链条进行传播，如果有函数抛出异常，就会在调用```info_to_display.get()```时抛出，捕获结构可以处理所有的异常类型

因为等待消息需要通过网络或数据操作进行传输，所函数内部会对后端模块进行调用，但这时前端的任务可能还没有完成。虽然已经将任务进行分割成独立的小任务，但仍然会阻塞线程的运行。这些需要在后端任务完成，前端处理就已经准备好了，而不是对线程进行阻塞。这样的话，```backend.async_authenticate_user(username, password)```返回 ```std::experimental::future<user_id>``` 会比返回user_id更加合适。

因为**持续函数返回的future类型为 ```future<future<some_value>>```** ，可能觉得这段代码比较复杂，否则只能将调用 .then 的语句放置在持续函数中。如果这么想就错了，因为持续性支持一种极为精妙的特性，叫做 **```future隐式展开(future-implicit-unwrapping)```**。当向 ```.then()``` 传递了持续性函数，并且返回一个future类型的值时，相应的 ```.then()``` 返回值类型也是future。最终的代码可能如下所示，这样在**异步函数链上就不会阻塞**

代码4.21 处理用户登录——全异步操作

```` cpp
std::experimental::future<void> process_login(std::string const& username,
                                              std::string const& password) {
  return backend.async_authenticate_user(username, password)
      .then([](std::experimental::future<user_id> id) { // C++14 可以使用auto进行替换
        return backend.async_request_current_info(id.get());
      })
      .then([](std::experimental::future<user_data> info_to_display) { // C++14 可以使用auto进行替换
        try {
          update_display(info_to_display.get());
        } catch (std::exception& e) {
          display_error(e);
        }
      });
}
````

```std::experimental::shared_future``` 同样支持持续性。二者的区别在于 ```std::experimental::shared_future``` 对象可以具有多个持续性对象，并且持续性参数是 ```std::experimental::shared_future``` ，而不是 ```std::experimental::future```

```` cpp
auto fut = spawn_async(some_function).share();
auto fut2 = fut.then([](std::experimental::shared_future<some_data> data){
  do_stuff(data);
});
auto fut3 = fut.then([](std::experimental::shared_future<some_data> data){
  return do_other_stuff(data);
});
````

fut是 ```std::experimental::share_future``` 实例，这是因为持续性函数必须将 ```std::experimental::shared_future``` 对象作为参数。不过，持续性(then)返回的值为 ```std::experimental::future``` ——目前这个值无法共享——所以fut2和fut3的类型都是 ```std::experimental::future```

### 4.4.5 等待多个future

假设有很多的数据需要处理，每个数据都可以单独的进行处理，这就是利用硬件的好机会。可以使用异步任务组来处理数据项，每个任务通过future返回处理结果。不过，需要等待所有任务完成，才能得到最终的结果。对逐个future进行收集，然后再整理结果，总感觉不是很爽。如果用异步任务来收集结果，先要生成异步任务，这样就会占用线程的资源，并且需要不断的对future进行轮询，当所有future状态为就绪时生成新的任务

代码4.22 使用 std::async 从多个future中收集结果

```` cpp
std::future<FinalResult> process_data(std::vector<MyData>& vec) {
  size_t const chunk_size = whatever;
  std::vector<std::future<ChunkResult>> results;
  for (auto begin = vec.begin(), end = vec.end(); beg != end;) {
    size_t const remaining_size = end - begin;
    size_t const this_chunk_size = std::min(remaining_size, chunk_size);
    results.push_back(
        std::async(process_chunk, begin, begin + this_chunk_size));
    begin += this_chunk_size;
  }
  return std::async([all_results = std::move(results)]() {
    std::vector<ChunkResult> v;
    v.reserve(all_results.size());
    for (auto& f : all_results) {
      v.push_back(f.get());  // 1
    }
    return gather_results(v);
  });
}
````

每个任务都是独立的，因此调度程序会在①处反复的进行唤醒，当发现有非就绪态的结果时，将再次回到休眠的状态。这样的方式不仅会占用线程资源，而且在之后对future的操作会增加上下文切换频率，从而增加很多额外的开销

可以使用 std::experimental::when_all 来避免这里的等待和切换，可以将需要等待的future传入when_all函数中，函数会返回新的future——当传入的future状态都为就绪时，新future的状态就会置为就绪，这个future可以和持续性配合起来处理其他的任务

代码4.23 使用 std::experimental::when_all 从多个future中收集结果

```` cpp
std::experimental::future<FinalResult> process_data(std::vector<MyData>& vec) {
  size_t const chunk_size = whatever;
  std::vector<std::experimental::future<ChunkResult>> results;
  for (auto begin = vec.begin(), end = vec.end(); beg != end) {
    size_t const remaining_size = end - begin;
    size_t const this_chunk_size = std::min(remaining_size, chunk_size);
    results.push_back(
        spawn_async(process_chunk, begin, begin + this_chunk_size));
    begin += this_chunk_size;
  }
  return std::experimental::when_all(results.begin(), results.end())
  // when_all 的该重载版本返回 std::vector<std::experimental::future<>>
      .then(  // 1
          [](std::future<std::vector<std::experimental::future<ChunkResult>>>
                 ready_results) {
            std::vector<std::experimental::future<ChunkResult>> all_results =
                ready_results.get();
            std::vector<ChunkResult> v;
            v.reserve(all_results.size());
            for (auto& f : all_results) {
              v.push_back(f.get());  // 2
            }
            return gather_results(v);
          });
}
````

### 4.4.6 使用when_any等待第一个future

假设要在一大堆数据里面找一个符合要求的值(符合这样要求的值有很多)，找到任何一个即可。这种任务是可
以并行的，可以多线程完成，每个任务去检查数据的一个子集，如果有线程找到了合适的值，这个线程就会
设置一个标志，让其他线程停止搜索，并返回结果。这种情况下，一般还希望第一个完成搜索任务的线程，能对
数据进行进一步的处理。

可以使用 ```std::experimental::when_any``` 将future收集在一起，当future有一个为就绪时，任务即为完成。when_all会根据传入的future集合返回一个新的future，when_any会添加额外的层，并将集合和索引值组合在一起，这里的索引用于表示触发就绪的future，并将这个future添加到 std::experimental::when_any_result 类模板实例中。

代码4.24 使用 std::experimental::when_any 处理第一个被找到的值

```` cpp
std::experimental::future<FinalResult> find_and_process_value(
    std::vector<MyData>& data) {
  unsigned const concurrency = std::thread::hardware_concurrency();
  unsigned const num_tasks = (concurrency > 0) ? concurrency : 2;
  std::vector<std::experimental::future<MyData*>> results;
  auto const chunk_size = (data.size() + num_tasks - 1) / num_tasks;
  auto chunk_begin = data.begin();

  std::shared_ptr<std::atomic<bool>> done_flag =
      std::make_shared<std::atomic<bool>>(false);
      
  for (unsigned i = 0; i < num_tasks; ++i) {  // 1
    auto chunk_end =
        (i < (num_tasks - 1) ? chunk_begin + chunk_size : data.end());
    results.push_back(spawn_async([=] {  // 2
      for (auto entry = chunk_begin; !*done_flag && (entry != chunk_end);
           ++entry) {
        if (matches_find_criteria(*entry)) {
          *done_flag = true;
          return &*entry;
        }
      }
      return (MyData*)nullptr;
    }));
    chunk_begin = chunk_end;
  }

  std::shared_ptr<std::experimental::promise<FinalResult>> final_result =
      std::make_shared<std::experimental::promise<FinalResult>>();

  struct DoneCheck {
    std::shared_ptr<std::experimental::promise<FinalResult>> final_result;
    DoneCheck(
        std::shared_ptr<std::experimental::promise<FinalResult>> final_result_)
        : final_result(std::move(final_result_)) {}
    void operator()(  // 4
        std::experimental::future<std::experimental::when_any_result<
            std::vector<std::experimental::future<MyData*>>>> results_param) {
      auto results = results_param.get();

      MyData* const ready_result = results.futures[results.index].get();  // 5
      if (ready_result)
        final_result->set_value(  // 6
            process_found_value(*ready_result));
      else {
        results.futures.erase(results.futures.begin() + results.index);  // 7
        if (!results.futures.empty()) {
          std::experimental::when_any(  // 8
              results.futures.begin(), results.futures.end())
              .then(std::move(*this));
        } else {
          final_result->set_exception(std::make_exception_ptr(  // 9
              std::runtime_error("Not found")));
        }
      }
    }
  };

  std::experimental::when_any(results.begin(), results.end())
      .then(DoneCheck(final_result));  // 3
  return final_result->get_future();   // 10
}
````

这两个使用when_all和when_any的例子中，都使用了重载版的迭代器范围，使用一堆迭代器来表示一组处于等待状态future的开始和末尾。这两个函数也可以以变量的形式出现，可以将一组future作为参数直接进行传入。例子中，future中存储的是元组(或when_any_result持有一个元组)，而不是vector：

```` cpp
std::experimental::future<int> f1=spawn_async(func1);
std::experimental::future<std::string> f2=spawn_async(func2);
std::experimental::future<double> f3=spawn_async(func3);
std::experimental::future<
std::tuple<std::experimental::future<int>,
std::experimental::future<std::string>,
std::experimental::future<double>>> result=
std::experimental::when_all(std::move(f1),std::move(f2),std::move(f3));
````

这个例子强调了when_any和when_all的重要性——可以通过容器中的任意 std::experimental::future 实例进行移动，并且通过值获取参数，因此需要显式的将future传入，或是传递一个临时变量。

### 4.4.7 锁存器和栅栏

有时等待的事件是一组线程，或是代码的某个特定点，亦或是协助处理一定量的数据。这种情况下，最好使用锁存器或栅栏，而非future。

**锁存器或是栅栏是什么东西？**

1. 锁存器是一种同步对象，当计数器减为0时，就处于就绪态了。锁存器是基于其输出特性——当处于就绪态时，就会保持就绪态，直到被销毁。因此，锁存器是为同步一系列事件的轻量级机制。

2. 栅栏是一种可复用的同步机制，其用于一组线程间的内部同步。

虽然，锁存器不在乎是哪个线程使得计数器递减——同一个线程可以对计数器递减多次，或多个线程对计数器递减一次，再或是有些线程对计数器有两次的递减——对于栅栏来说，每一个线程只能在每个周期到达栅栏一次。当线程抵达栅栏时，会对线程进行阻塞，直到所有线程都达到栅栏处，这时阻塞将会被解除。栅栏可以复用——线程可以再次到达栅栏处，等待下一个周期的所有线程。

### 4.4.8 std::latch：基础的锁存器类型

```std::latch``` 声明在 ```<latch>``` 头文件中(C++20之前在 ```<experimental/latch>```)。构造 ```std::latch``` 时，将计数器的值作为构造函数的唯一参数。当等待的事件发生，就会调用锁存器 **```count_down```** 成员函数。当计数器为0时，锁存器状态变为就绪。可以调用```wait```成员函数对锁存器进行阻塞，直到等待的锁存器处于就绪状态。如果需要对锁存器是否就绪的状态进行检查，可调用```is_ready```成员函数。想要减少计数器1并阻塞直至0，则可以调用 **```count_down_and_wait```** 成员函数。

代码4.25 使用 std::latch 等待所有事件

```` cpp
void foo() {
  unsigned const thread_count = ...;
  latch done(thread_count);  // 1
  my_data data[thread_count];
  std::vector<std::future<void> > threads;
  for (unsigned i = 0; i < thread_count; ++i)
    threads.push_back(std::async(std::launch::async, [&, i] {  // 2
      data[i] = make_data(i);
      done.count_down();  // 3
      do_more_stuff();    // 4
    }));
  done.wait();                       // 5
  process_data(data, thread_count);  // 6
}  // 7
````

### 4.4.9 std::barrier：简单的栅栏

并发技术扩展规范提供了两种栅栏机制， 分别位于```<barrier> 和 <experimental/barrier>``` 头文件中(C++20前都在 ```<experimental/barrier>```)，分别为： ```std::barrier``` 和 ```std::experimental::flex_barrier```。前者更简单，开销更低。后者更灵活，开销较大。

假设有一组线程对某些数据进行处理。每个线程都在处理独立的任务，因此在处理过程中无需同步。但当所有线程都必须在处理下一个数据项前完成当前的任务时，就可以使用 ```std::barrier``` 来完成这项工作了

可以为同步组指定线程的数量，并为这组线程构造栅栏。当每个线程完成其处理任务时，都会到达栅栏处，并且通过调用栅栏对象的```arrive_and_wait```成员函数，等待小组的其他线程。当最后一个线程抵达时，所有线程将被释放，栅栏重置。组中的线程可以继续接下来的任务，或是处理下一个数据项，或是进入下一个处理阶段

锁存器一旦就绪就会保持状态，不会有释放等待线程、重置、复用的过程。栅栏也只能用于一组线程内的同步——除非组中只有一个线程，否则无法等待栅栏就绪。

可以通过显式调用栅栏对象的```arrive_and_drop```成员函数让线程退出组，这样就不用再受栅栏的约束，这样下一个周期到达的线程数就要比当前周期到达的线程数少一个了

代码4.26 ```std::barrier``` 的用法

```` cpp
result_chunk process(data_chunk);

std::vector<data_chunk> divide_into_chunks(data_block data,
                                           unsigned num_threads);

void process_data(data_source& source, data_sink& sink) {
  unsigned const concurrency = std::thread::hardware_concurrency();
  unsigned const num_threads = (concurrency > 0) ? concurrency : 2;

  std::barrier sync(num_threads);
  std::vector<joining_thread> threads(num_threads);
  std::vector<data_chunk> chunks;
  result_block result;
  for (unsigned i = 0; i < num_threads; ++i) {
    threads[i] = joining_thread([&, i] {
      while (!source.done()) {  // 6
        if (!i) {               // 1
          data_block current_block = source.get_next_data_block();
          chunks = divide_into_chunks(current_block, num_threads);
        }
        sync.arrive_and_wait();                                // 2
        result.set_chunk(i, num_threads, process(chunks[i]));  // 3
        sync.arrive_and_wait();                                // 4
        if (!i) {                                              // 5
          sink.write_data(std::move(result));
        }
      }
    });
  }
}  // 7
````

需要着重注意的是arrive_and_wait的调用位置。所有线程就绪前，确定没有运行线程这点很重要。第一个同步点，所有线程都在等待0号线程到达。而第二个同步点，情况刚好相反，0号线程在等待其他线程都到达之后，才能将完成的结果写入sink中。

### 4.4.10 std::experimental::flex_barrier (更灵活和更友好的std::barrier)

与 ```std::barrier``` 相同， ```std::experimental::flex_barrier``` 这个类型的栅栏更加的灵活。灵活之处在于，栅栏拥有**完成阶段**，一旦参与线程集中的所有线程都到达同步点，则由参与线程之一去执行完成阶段。

```std::experimental::flex_barrier```有一个额外的构造函数，需要传入一个完整的函数和线程数量，当所有线程都到达栅栏处，那么这个函数就由其中一个线程运行。其不仅指定了串行代码的运行方式，还提供了一种修改下一个周期到达栅栏处线程个数的方式。对于线程的计数可以修改成任何数字，无论这个数字比当前数字高或低。这样，开发者就能确定下一次到达栅栏处的线程数量了。

代码4.27 使用 std::experimental::flex_barrier 管理串行部分

```` cpp
void process_data(data_source& source, data_sink& sink) {
  unsigned const concurrency = std::thread::hardware_concurrency();
  unsigned const num_threads = (concurrency > 0) ? concurrency : 2;
  std::vector<data_chunk> chunks;

  auto split_source = [&] {  // 1
    if (!source.done()) {
      data_block current_block = source.get_next_data_block();
      chunks = divide_into_chunks(current_block, num_threads);
    }
  };
  split_source();  // 2

  result_block result;
  std::experimental::flex_barrier sync(num_threads, [&] {  // 3
    sink.write_data(std::move(result));
    split_source();  // 4
    return -1;       // 5 
    // 返回值-1表示线程数目保持不变，返回值为 0 或 其他数值 则指定的是下一个周期中参与迭代的线程数量。
  });

  std::vector<joining_thread> threads(num_threads);
  for (unsigned i = 0; i < num_threads; ++i) {
    threads[i] = joining_thread([&, i] {
      while (!source.done()) {  // 6
        result.set_chunk(i, num_threads, process(chunks[i]));
        sync.arrive_and_wait();  // 7
      }
    });
  }
}
````

**使用完整函数作为串行块**是一种很强大的功能，因为这能够改变参与并行的线程数量。例如：流水线类型代码在运行时，当流水线的各级都在进行处理时，线程的数量在初始阶段和执行阶段要少于主线程处理阶段。

## 4.5 本章总结

本章讨论了各式各样的同步操作，有条件变量、future、promise、打包任务、锁存器和栅栏。还讨论了替代同步的解决方案：函数式编程，完全独立执行的函数，不会受到外部环境的影响，以及消息传递模式，以消息子系统为中介，向线程异步的发送消息和持续性方式，其指定了操作的后续任务，并由系统负责调度。

已经讨论了很多C++中的高层工具，现在我们来看一下底层工具是如何工作的：C++内存模型和原子操作。
