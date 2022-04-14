// reference：https://en.cppreference.com/w/cpp/language/coroutines

// 协程（C++20起）就是一个可以挂起(suspend)和恢复(resume)的函数(但无论如何不能是
// main 函数)。
// 即你可以暂停协程的执行，去做其他事情，然后在适当的时候恢复到暂停的位置继续执行。
// 协程是无堆栈的：它们通过返回给调用者来暂停执行，并且恢复执行所需的数据与堆栈分开存储
// 这支持了顺序代码的异步执行（例如，在没有显式回调的情况下处理非阻塞 I/O）
// 并且还支持惰性计算无限序列和其他用途的算法。

// Note: coroutine 不是并行(parallelism)，和 Go 语言的 goroutine 不一样！

#include <coroutine>
#include <iostream>
#include <stdexcept>
#include <thread>

// 如果函数的定义执行以下任何一项，则该函数是协程：
// 1. 使用 co_await 操作符 暂停执行直到恢复

// #define Coroutine
#ifdef Coroutine
task<> tcp_echo_server() {
  char data[1024];
  while (true) {
    size_t n = co_await socket.async_read_some(buffer(data));
    co_await async_write(socket, buffer(data, n));
  }
}

// 2. 使用关键字 co_yield 暂停执行并返回一个值

generator<int> iota(int n = 0) {
  while (true)
    co_yield n++;
}

// 3. 使用关键字 co_return 完成执行并返回一个值

lazy<int> f() {
  co_return 7;
}
#endif

// 每个协程的返回类型都必须满足许多要求，如下所述。
// 1. 协程不能使用可变参数、朴素返回语句或占位符返回类型（auto 或 Concept）。
// 2. constexpr 函数、构造函数、析构函数和 main函数不能是协程。

// 每个协程都有：
// 1. 在协程内部操纵的 promise 对象，协程通过此对象提交其结果或异常。
// 2. 协程外部操纵的 coroutine handle（协程句柄），这是一个没有所有权的句柄，用于恢复协程的执行或销毁协程框架。
// 3. coroutine state（协程状态），这是一个协程内部的堆分配的对象（除非分配被优化），包括：
//    1. promise 对象
//    2. 参数（全部按值复制）
//    3. 当前暂停点的某种表示，以便 resume
//    知道在哪里继续，destroy知道哪些局部变量在范围内
//    4. 生命周期大于当前挂起点的局部变量和临时变量

// 当协程开始执行时，它会执行以下操作：
// 1. 使用 operator new 分配 coroutine state 对象
// 2. 将所有函数参数复制到coroutine state：移动 或 复制 按值传递的参数，
//    按引用传递参数保持引用（**Note**:
//    因此如果在引用对象的生命周期结束后恢复协程，则可能会变得悬空）

struct promise;
struct coroutine : std::coroutine_handle<promise> {
  using promise_type = struct promise;
};

struct promise {
  coroutine get_return_object() { 
    std::cout << "get in promise::get_return_object()\n";
    return {coroutine::from_promise(*this)}; 
  }
  std::suspend_always initial_suspend() noexcept { 
    std::cout << "get in promise::initial_suspend()\n";
    return {}; 
  }
  std::suspend_never final_suspend() noexcept { 
    std::cout << "get in promise::final_suspend()\n";
    return {}; 
  }
  void return_void() {
    std::cout << "get in promise::return_void()\n";
  }
  void unhandled_exception() {
    std::cout << "get in promise::unhandled_exception()\n";
  }
  promise() {
    std::cout << "promise::promise\n"; 
  }

  void* operator new(size_t size) {
    std::cout << "new " << size << " bytes\n"; 
    return malloc(size); 
  }

  void operator delete(void* p, size_t size) {
    std::cout << "delete " << size << " bytes on " << p << "\n"; 
    free(p); 
  }
};

// 1. 如果 Promise 类型有一个接受所有协程参数的构造函数，则调用该构造函数，并带有复制后的协程参数。
//    否则调用默认构造函数。
// 2. 当协程第一次挂起时，调用 promise.get_return_object()
//    并将结果保存在一个局部变量中。该调用的结果将返回给调用者。
// 3. 调用 promise.initial_suspend() 并 co_await 其结果。
//    典型的 Promise 类型要么返回一个 suspend_always，用于延迟启动的协程，
//    要么返回一个 suspend_never，用于急切启动的协程。
// 4. 当 co_await promise.initial_suspend() resume时，开始执行协程主体

// 当协程到达暂停点时，如果需要，在隐式转换为协程的返回类型后，将之前获得的返回对象返回给调用者/恢复者。
// 协程到达 co_return 时，执行：
//    - 以下情况调用 promise.return_void()
//       1. co_return;
//       2. co_return expr; expr类型为void
//       3. 从返回 void 的协程的末尾掉落。在这种情况下，如果 Promise 没有 Promise::return_void() 成员函数，则行为未定义。
//    - 以下情况调用 promise.return_value(expr)
//       1. co_return expr; expr类型不为void
//    - 以创建时相反的顺序销毁所有具有自动存储时间的变量。
//    - 调用 promise.final_suspend() 并 co_await 结果。

// 如果协程以未捕获的异常结束，它将执行以下操作：
//    - 捕获异常并从 catch-block 中调用 promise.unhandled_exception()
//    - 调用 promise.final_suspend() 并 co_await 结果（例如，恢复延续或发布结果）。
//      从这一点恢复协程是未定义的行为。

// 当 coroutine state 因为 co_return 或 未捕获的异常终止，或者因为它的句柄被销毁而被销毁时，它会执行以下操作:
//    - 调用 promise 对象的析构函数。
//    - 调用函数参数副本的析构函数。
//    - 调用 operator delete 释放 coroutine state 所使用的内存
//    - 将执行转移回调用者/恢复者。

// 关于 coroutine state 的堆内存分配
// coroutine state 使用 operator new分配内存，
// 如果 promise 重载了 operator new 则使用该 operator new，否则使用全局 operator new
// 如果 重载的 member operator new 还有额外的参数（除了第一个size_t），并且剩余的参数与协程的参数相匹配，
// 那么这些参数将会传递给该 operator new（这使得对协程使用
// 《前导分配器约定》[https://en.cppreference.com/w/cpp/memory/uses_allocator#Uses-allocator_construction]
// 成为可能）

// operator new 的调用可能会被优化（即使使用自定义分配器）如果:
//    1. coroutine state 的生命周期严格嵌套在调用者的生命周期内，并且
//    2. 协程帧的大小在协程状态已知
// 这种情况下，协程状态将会嵌入在调用者的堆栈帧中（如果调用者是普通函数）或 coroutine state （如果调用者是协程）
// 如果分配失败，协程抛出异常 std::bad_alloc，
// 除非 Promise 类型定义了成员函数 Promise::get_return_object_on_allocation_failure()
// 如果定义了该成员函数，则分配使用运算符 new 的 nothrow 形式，并且在分配失败时，
// 协程立即将从 Promise::get_return_object_on_allocation_failure() 获得的对象返回给调用者。


struct S {
  int i;
  coroutine f() {
    std::cout << i;
    co_return;
  }
};

void bad1() {
  coroutine h = S{0}.f();
  // S{0} destroyed
  h.resume();  // resumed coroutine executes std::cout << i, uses S::i after
               // free
  h.destroy();
}

coroutine bad2() {
  S s{0};
  return s.f();  // returned coroutine can't be resumed without committing use
                 // after free
}

void bad3() {
  coroutine h = [i = 0]() -> coroutine {  // a lambda that's also a coroutine
    std::cout << i;
    co_return;
  }();  // immediately invoked
  // lambda destroyed
  h.resume();  // uses (anonymous lambda type)::i after free
  h.destroy();
}

void good() {
  coroutine h = [](int i) -> coroutine {  // make i a coroutine parameter
    std::cout << i << std::endl;
    // throw std::runtime_error("throw an error");
    co_return;
  }(0);
  // lambda destroyed
  h.resume();  // no problem, i has been copied to the coroutine frame as a
               // by-value parameter
  h.destroy();
}


// Promise对象
// Promise 类型由编译器使用 std::coroutine_traits 的返回类型确定。
// if the coroutine is not defined as a non-static member function,
// std::coroutine_traits<R, Args...>::promise_type, 

// if the coroutine is defined as a non-static member function that is not rvalue-reference-qualified,
// std::coroutine_traits<R, ClassT /*cv-qual*/&, Args...>::promise_type,

// if the coroutine is defined as a non-static member function that is rvalue-reference-qualified.
// std::coroutine_traits<R, ClassT /*cv-qual*/&&, Args...>::promise_type, 

// For example:
// If the coroutine is defined as task<float> foo(std::string x, bool flag);, 
// then its Promise type is std::coroutine_traits<task<float>, std::string, bool>::promise_type.
// If the coroutine is defined as task<void> my_class::method1(int x) const;,
// its Promise type is std::coroutine_traits<task<void>, const my_class&, int>::promise_type.
// If the coroutine is defined as task<void> my_class::method1(int x) &&;,
// its Promise type is std::coroutine_traits<task<void>, my_class&&, int>::promise_type.





// operator co_await
// The unary operator co_await suspends a coroutine and returns control to the caller. 
// Its operand is an expression whose type must either define operator co_await, 
// or be convertible to such type by means of the current coroutine's Promise::await_transform

// co_await expr		
// 首先，将 expr 转换为 awaitable 对象，如下所示:
// 1. 如果 expr 由初始挂起点、最终挂起点或 yield 表达式产生，则可等待对象是 expr，原样。
// 2. 否则，如果当前协程的 Promise 类型有成员函数 await_transform，那么 awaitable 就是 promise.await_transform(expr)
// 3. 否则，等待是 expr，原样。

// 然后获得 awaiter 对象
// 1. 如果 operator co_await 的重载决议给出了单个最佳重载，则 awaiter 是该调用的结果
//    ( 对于成员重载，awaitable.operator co_await()，对于非成员重载，
//    operator co_await(static_cast<Awaitable&&>(awaitable)) )
// 2. 否则，如果重载解决方案没有找到操作符 co_await，the awaiter is awaitable,
// 3. 否则，如果重载决议不明确，则程序格式错误
// 如果上面的表达式是纯右值，则 awaiter 对象是它的临时物化对象。
// 否则，如果上面的表达式是一个泛左值，那么 awaiter 对象就是它所引用的对象。

// 然后，调用 awaiter.await_ready() （如果知道结果已准备好或可以同步完成，这是避免挂起成本的捷径）。
// 如果其结果依据上下文转换为 bool 为假，则该协程被挂起 (suspended), (它的协程状态由局部变量和当前暂停点填充)，并且
//    1. awaiter.await_suspend(handle) 被调用，其中 handle 是表示当前协程的协程句柄。
//       在该函数(awaiter.await_suspend)内部，可以通过该句柄观察挂起的协程状态，
//       并且该函数负责安排它在某个执行程序上恢复或被销毁（返回 false counts 作为调度）   
//    2. 如果 await_suspend 返回 void，则立即将控制权返回给当前协程的 caller/resumer（此协程保持挂起状态）
//    3. 如果 await_suspend 返回布尔值，
//       为true: 将控制权返回给当前协程的 caller/resumer（此协程保持挂起状态）
//       为false: 恢复当前协程。
//    4. 如果 await_suspend 返回某个其他协程的协程句柄，则恢复该句柄 (通过调用 handle.resume())
//       (Note: 可能通过 resume 传播导致当前协程恢复)
//    5. 如果 await_suspend 抛出异常，则捕获异常，恢复协程并立即重新抛出异常

// 最终 awaiter.await_resume() 被调用，它的结果是整个 co_await expr 表达式的结果
// 如果协程在 co_await 表达式中被挂起，然后又被恢复，那么恢复点就在调用 awaiter.await_resume() 之前。
// Note: 因为协程在进入 awaiter.await_suspend() 之前就完全挂起, 该函数可以自由地跨线程传输协程句柄，无需额外同步。
// 例如，它可以将它放在一个回调中，安排在异步 I/O 操作完成时在线程池上运行。
// 在这种情况下，由于当前协程可能已经 resume 并因此执行了 awaiter 对象的析构函数，
// await_suspend() 应该将 *this 视为已销毁，并且在句柄发布到其他线程后不访问它。

auto switch_to_new_thread(std::jthread& out) {
  struct awaitable {
    std::jthread* p_out;
    bool await_ready() { 
      std::cout << "get in awaitable::await_ready() and return false\n"; 
      return false; 
    }
    bool await_suspend(std::coroutine_handle<> h) {
      std::cout << "get in awaitable::coroutine_handle()\n"; 
      std::jthread& out = *p_out;
      if (out.joinable())
        throw std::runtime_error("Output jthread parameter not empty");
      out = std::jthread([h] {
        std::cout << "get in std::jthread\n"; 
        h.resume(); 
      });
      // Potential undefined behavior: accessing potentially destroyed *this
      // std::cout << "New thread ID: " << p_out->get_id() << '\n';
      std::cout << "New thread ID: " << out.get_id() << '\n'; // this is OK
      return true; 
    }
    void await_resume() {
      std::cout << "get in awaitable::await_resume()\n"; 
    }
    
  };
  return awaitable{&out};
}

struct task{
  struct promise_type {
    task get_return_object() { return {}; }
    std::suspend_never initial_suspend() { return {}; }
    std::suspend_never final_suspend() noexcept { return {}; }
    void return_void() {}
    void unhandled_exception() {}
  };
};
 
task resuming_on_new_thread(std::jthread& out) {
  std::cout << "Coroutine started on thread: " << std::this_thread::get_id() << '\n';
  co_await switch_to_new_thread(out);
  // awaiter destroyed here
  std::cout << "Coroutine resumed on thread: " << std::this_thread::get_id() << '\n';
}

// Note: awaiter 对象是协程状态的一部分, (作为一个临时的，其生命周期跨越一个暂停点), 
// 并在 co_await 表达式完成之前被销毁。
// 它可用于根据某些异步 I/O API 的要求维护每个操作的状态，而无需求助于额外的堆分配。
// 标准库定义了两个微不足道的 awaiter：std::suspend_always 和 std::suspend_never。


// expression Yield
// Yield-expression 向调用者返回一个值并暂停当前协程：它是可恢复生成器函数的通用构建块

// 形式：
// co_yield expr		
// co_yield braced-init-list		

// 等价于
// co_await promise.yield_value(expr)
// 典型生成器的 yield_value 会将其参数存储（复制/移动或仅存储地址，
// 因为参数的生命周期跨越 co_await 内的暂停点）生成器对象中并返回 std::suspend_always, 
// 将控制权转移给 caller/resumer。


template<typename T>
struct Generator {
   // The class name 'Generator' is our choice and 
   // it is not required for coroutine magic. 
   // Compiler recognizes coroutine by the presence of 'co_yield' keyword.
   // You can use name 'MyGenerator' (or any other name) instead
   // as long as you include nested struct promise_type 
   // with 'MyGenerator get_return_object()' method .
   //(Note:You need to adjust class constructor/destructor names too when choosing to rename class)
 
  struct promise_type;
  using handle_type = std::coroutine_handle<promise_type>;
 
  struct promise_type {// required 
    T value_;
    std::exception_ptr exception_;
 
    Generator get_return_object() {
      std::cout << "get in Generator::promise_type::get_return_object()" << std::endl; 
      return Generator(handle_type::from_promise(*this));
    }
    std::suspend_always initial_suspend() { 
      std::cout << "get in Generator::promise_type::initial_suspend()" << std::endl; 
      return {}; 
    }
    std::suspend_always final_suspend() noexcept { 
      std::cout << "get in Generator::promise_type::final_suspend()" << std::endl; 
      return {}; 
    }
    void unhandled_exception() { exception_ = std::current_exception(); }//saving exception
    template<std::convertible_to<T> From> // C++20 concept
    std::suspend_always yield_value(From &&from) {
      std::cout << "get in Generator::promise_type::yield_value()" << std::endl; 
      value_ = std::forward<From>(from);//caching the result in promise
      return {};
    }
    void return_void() {
      std::cout << "get in Generator::promise_type::return_void()" << std::endl; 
    }
  };
 
  handle_type h_;
 
  Generator(handle_type h) : h_(h) {}
  ~Generator() { h_.destroy(); }
  explicit operator bool() {
    std::cout << "get in Generator::operator bool" << std::endl; 
    fill();// The only way to reliably find out whether or not we finished coroutine, 
           // whether or not there is going to be a next value generated (co_yield) in coroutine
           // via C++ getter (operator () below) 
           // is to execute/resume coroutine until the next co_yield point (or let it fall off end).
           // Then we store/cache result in promise to allow getter (operator() below to grab it 
           // without executing coroutine)
    return !h_.done();
  }
  T operator()() {
    std::cout << "get in Generator::operator()" << std::endl; 
    fill(); 
    full_ = false;//we are going to move out previously cached result to make promise empty again
    return std::move(h_.promise().value_);
  }
 
private:
  bool full_ = false;
 
  void fill() {
    std::cout << "get in Generator::fill()" << std::endl; 
    if (!full_) {
      h_();
      if (h_.promise().exception_)
        std::rethrow_exception(h_.promise().exception_);
        //propagate coroutine exception in called context
 
      full_ = true;
    }
  }
};
 
Generator<uint64_t>
fibonacci_sequence(unsigned n)
{
 
  if (n==0)
    co_return;
 
  if (n>94)
    throw std::runtime_error("Too big Fibonacci sequence. Elements would overflow.");
 
  co_yield 0;
 
  if (n==1)
    co_return;
 
  co_yield 1;
 
  if (n==2)
    co_return;
 
  uint64_t a=0;
  uint64_t b=1;
 
  for (unsigned i = 2; i < n;i++)
  {
    uint64_t s=a+b; 
    std::cout << "before co_yield s = " << s << std::endl; 
    co_yield s; 
    a=b; 
    b=s; 
  }
}


int main() {
  
  // promise: 
  good();

  // cowait: 
  // std::jthread out;
  // resuming_on_new_thread(out);

  try {
    auto gen = fibonacci_sequence(10);  // max 94 before uint64_t overflows
    std::cout << "before excute" << std::endl; 
    for (int j = 0; gen; j++)
      std::cout << "fib(" << j << ")=" << gen() << '\n';
  } catch (const std::exception& ex) {
    std::cerr << "Exception: " << ex.what() << '\n';
  } catch (...) {
    std::cerr << "Unknown exception.\n";
  }

  return 0;
}