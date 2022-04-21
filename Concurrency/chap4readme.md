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

