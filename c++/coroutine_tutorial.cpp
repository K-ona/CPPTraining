// https://www.bennyhuo.com/book/cpp-coroutines/
#include <coroutine>
#include <chrono>
#include <thread>
#include <future>
#include <optional>
#include <mutex>
#include <iostream>
#include <condition_variable>
#include <list>

// 1. C++ 协程概览
// #define CO_1
#ifdef CO_1

struct Awaiter {
  int value;

  bool await_ready() {
    // 协程挂起
    return false;
  }

  void await_suspend(std::coroutine_handle<> coroutine_handle) {
    // 切换线程
    std::async([=](){
      using namespace std::chrono_literals;
      // sleep 1s
      std::this_thread::sleep_for(1s); 
      // 恢复协程
      coroutine_handle.resume();
    });
  }

  int await_resume() {
    // value 将作为 co_await 表达式的值
    return value;
  }
};

struct Result {

  struct promise_type {
      int value; 
      std::suspend_never initial_suspend() {
        std::cout << "get in Generator::promise_type::initial_suspend()" << std::endl; 
        return {}; 
      }
      std::suspend_always final_suspend() noexcept {
        std::cout << "get in Generator::promise_type::final_suspend()" << std::endl; 
        return {}; 
      }

      void unhandled_exception() { }

      void return_value(int value_) {
        value = value_; 
      }

      // void return_void() {}

      Result get_return_object() {
        std::cout << "get in promise::get_return_object()\n";
        return {}; 
      }
  };

  int operator()() {
    return 0; 
  }
};


Result Coroutine() {
  std::cout << 1 << std::endl;
  std::cout << co_await Awaiter{.value = 1000} << std::endl;
  std::cout << 2 << std::endl; // 1 秒之后再执行

  co_return 1; 
};

int main() {
  auto x = Coroutine(); 
  x();
}
#endif

// 2. 实现一个序列生成器

// #define CO_2
#ifdef CO_2

struct Generator {
  struct promise_type {
    int value; 
    bool is_ready = false; 

    std::suspend_always initial_suspend() { return {}; }
    
    // 选择挂起，让Generator自己销毁协程
    std::suspend_always final_suspend() noexcept  { return {}; }

    Generator get_return_object() {
      return Generator{ std::coroutine_handle<promise_type>::from_promise(*this) };
    }

    void unhandled_exception() {}

    void return_void() {}

    // 为得到 waiter对象 方案1：为promise_type 实现一个 await_transform(int)
    std::suspend_always await_transform(int value) {
      this->value = value; 
      is_ready = true; 
      return {}; 
    }

    // yield expr = coawait promise.yield_value(expr)
    // 尽管可以实现相同的效果，但通常情况下我们使用 co_await 更多的关注点在挂起自己，
    // 等待别人上，而使用 co_yield 则是挂起自己传值出去。因此我们应该针对合适的场景做出合适的选择。
    std::suspend_always yield_value(int value) {
      this->value = value; 
      is_ready = true; 
      return {}; 
    }
  };

  std::coroutine_handle<promise_type> handle; 

  int next() {
    if (has_next()) {
      handle.promise().is_ready = false; 
      return handle.promise().value; 
    }
    throw ExhaustedException(); 
  }

  bool has_next() {
    // 执行完毕
    if (handle.done()) {
      return false; 
    }

    if (!handle.promise().is_ready) {
      handle.resume(); 
    }

    if (handle.done()) {
      return false; 
    } return true;
  }
  class ExhaustedException: std::exception {}; 

  ~Generator() {
    if (handle) handle.destroy(); 
  }

  explicit Generator(std::coroutine_handle<promise_type> handle)
    noexcept : handle(handle) {}

  Generator(Generator&& generator) noexcept :
    handle(std::exchange(generator.handle, {})){}

  Generator(Generator &) = delete;
  Generator& operator=(const Generator&) = delete; 
};

// 为得到 waiter对象 方案2：为 co_await 的参数类型重载一个 co_await 运算符
// 本例中 参数类型为基本类型，C++不支持为基本类型定义运算符重载
// auto operator co_await(int value) {
//   struct IntAwaiter {
//     int value;
//     bool await_ready() const noexcept {
//       return false;
//     }
//     void await_suspend(std::coroutine_handle<Generator::promise_type> handle) const {
//       handle.promise().value = value;
//     }
//     void await_resume() {  }
//   };
//   return IntAwaiter{.value = value};
// }


Generator sequence() {
  int i = 0; 
  while (true) {
    // co_await i++;
    co_yield i++;
  }
}

Generator fibonacci() {
  co_yield 0; // fib(0)
  co_yield 1; // fib(1)

  int a = 0;
  int b = 1;
  while(true) {
    co_yield a + b; // fib(N), N > 1
    b = a + b;
    a = b - a;
  }
}


int main() {
  auto generator = sequence();
  for (int i = 0; i < 10; ++i) {
    std::cout << generator.next() << std::endl;
  }

  auto fib = fibonacci();
  for (int i = 0; i < 10; ++i) {
    std::cout << fib.next() << std::endl;
  }
}
#endif

// 3. 序列生成器的泛化和函数式变换

// #define generalization
#ifdef generalization

// 3.1 将generator泛化成模板类，对原代码进行改动

template<typename T>
struct Generator {
  struct promise_type {
    T value; 
    bool is_ready = false; 

    std::suspend_always initial_suspend() { return {}; }

    std::suspend_always final_suspend() noexcept  { return {}; }

    Generator get_return_object() {
      return Generator{ std::coroutine_handle<promise_type>::from_promise(*this) };
    }

    void unhandled_exception() {}

    void return_void() {}

    std::suspend_always await_transform(T value) {
      this->value = value; 
      is_ready = true; 
      return {}; 
    }

    std::suspend_always yield_value(T value) {
      this->value = value; 
      is_ready = true; 
      return {}; 
    }
  };

  std::coroutine_handle<promise_type> handle; 

  T next() {
    if (has_next()) {
      handle.promise().is_ready = false; 
      return handle.promise().value; 
    }
    throw ExhaustedException(); 
  }

  bool has_next() {
    // 执行完毕
    if (handle.done()) {
      return false; 
    }

    if (!handle.promise().is_ready) {
      handle.resume(); 
    }

    if (handle.done()) {
      return false; 
    } return true;
  }
  class ExhaustedException: std::exception {}; 

  ~Generator() {
    if (handle) handle.destroy(); 
  }

  explicit Generator(std::coroutine_handle<promise_type> handle)
    noexcept : handle(handle) {}

  Generator(Generator&& generator) noexcept :
    handle(std::exchange(generator.handle, {})){}

  Generator(Generator &) = delete;
  Generator& operator=(const Generator&) = delete; 

  // 3.2 使用数组等创建generator
  template<size_t N>
  Generator static from(T (&array)[N]) {
    for (size_t i = 0; i < N; ++i)
      co_yield array[i]; 
  }

  Generator static from(std::initializer_list<T> list) {
    for (auto item: list) {
      co_yield item;
    }
  }

  // auto generator = Generator<int>::from(1, 2, 4); 
  template<typename ...Args>
  Generator static from(Args ...args) {
    (co_await args, ...);
  }


  // 3.3 实现map
  // map 就是将 Generator 当中的 T 映射成一个新的类型 U，
  // 得到一个新的 Generator<U>。
  // 第1个版本的 map 实现：

  // template<typename U>
  // Generator<U> map(std::function<U(T)> f) {
  //   while (has_next()) {
  //     co_yield f(next()); 
  //   }
  // }

  // 使用方法：
  // Generator<std::string> generator_str = fibonacci().map<std::string>([](int i) {
  //   return std::to_string(i);
  // });
  // 这个实现有个小小的缺陷，那就是 map 函数的模板参数 U 必须显式提供

  // 第2个版本的 map 实现：
  template<typename F>
  requires std::invocable<F, T>
  Generator<std::invoke_result_t<F, T>> map(F f) { 
    while (has_next()) {
      co_yield f(next()); 
    }
  }
  
  // 3.4 实现 flat_map
  template<typename F>
  requires std::invocable<F, T>
  std::invoke_result_t<F, T> flat_map(F f) { 
    while (has_next()) {
      auto generator = f(next()); 
      while (generator.has_next()) {
        co_yield generator.next(); 
      } 
    }
  }

  template<typename F>
  void for_each(F f) {
    while (has_next()) {
      f(next());
    }
  }

  template<typename R, typename F> 
  R fold(R initial, F f) {
    R acc = initial; 
    while (has_next()) {
      acc = f(acc, next()); 
    }
    return acc; 
  }

  T sum() {
    T sum{}; 
    while (has_next()) {
      sum += next(); 
    }
    return sum; 
  }

  template<typename F> 
  Generator filter(F f) {
    while (has_next()) {
      T value = next(); 
      if (f(value)) {
      co_yield value;
      }
    }
  }

  Generator take(size_t n) {
    while (n-- && has_next()) {
      co_yield next(); 
    }
  }

  template<typename F>
  Generator take_while(F f) {
    while (has_next()) {
      T value = next(); 
      if (f(value)) {
        co_yield value;
      } else {
        break;
      }
    }
  }
};

Generator<int> fibonacci() {
  co_yield 0; // fib(0)
  co_yield 1; // fib(1)

  int a = 0;
  int b = 1;
  while(a < 1000) {
    co_yield a + b; // fib(N), N > 1
    b = a + b;
    a = b - a;
  }
}

int main() {

  // auto fib = fibonacci();

  // Generator<std::string> generator_str =
  //     fib.map([](int i) { return std::to_string(i); });

  // while (fib.has_next()) {
  //   std::cout << fib.next() << " " << generator_str.next() << std::endl; 
  // }
  
  // 请牢记 Generator 生成的序列是懒序列，只要最终访问到的时候才会生成。
  // 这意味着中间的 map 其中根本不会主动消费 Generator，flat_map 也不会，filter 也不会，
  // take 也不会。只有 for_each 调用的时候，才会真正需要知道 Generator 当中都有什么。
  Generator<int>::from(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
    .filter([](auto i) {
      std::cout << "filter: " << i << std::endl;
      return i % 2 == 0;
    })
    .map([](auto i) {
      std::cout << "map: " << i << std::endl;
      return i * 3;
    })
    .flat_map([](auto i) -> Generator<int> {
      std::cout << "flat_map: " << i << std::endl;
      for (int j = 0; j < i; ++j) {
        co_yield j;
      }
    }).take(7)
    .for_each([](auto i) {
      std::cout << "for_each: " << i << std::endl;
    });
 
}
#endif

// 4. 通用异步任务 Task
// 协程主要用来降低异步任务的编写复杂度，异步任务各式各样，但归根结底就是一个**结果**的获取。

#define ASYNC_TASK
#ifdef ASYNC_TASK

#define Print(n) (std::cout << n << std::endl); 

// 定义结果类型
template<typename T>
struct Result {
  explicit Result() = default; 

  explicit Result(T&& _value) noexcept : value(_value) {} 

  explicit Result(std::exception_ptr &&_exception_ptr): exception_ptr(_exception_ptr) {}

  T get_or_throw() {
    if (exception_ptr) {
      std::rethrow_exception(exception_ptr); 
    }
    return value; 
  }
 private:
  T value{}; 
  std::exception_ptr exception_ptr;  
};

template<typename ResultType>
struct Task {

  template<typename _ResultType> 
  struct TaskPromise;

  using promise_type = TaskPromise<ResultType>; 

  ResultType get_result() {
    return handle.promise().get_result(); 
  }

  Task& then(std::function<void(ResultType)>&& func) {
    std::cout << "get in then" << std::endl; 
    handle.promise().on_completed([func] (auto result) {
      try {
        func(result.get_or_throw()); 
      } catch (std::exception &e) { 
      // 忽略异常
      }
    });
    return *this; 
  }

  Task& catching(std::function<void(std::exception&)>&& func) {
    std::cout << "get in catching" << std::endl; 

    handle.promise().on_completed([func](auto result) {
      try {
        // 忽略返回值
        result.get_or_throw(); 
      } catch (std::exception& e) {
        func(e); 
      }
    });
    return *this;
  }

  Task& finally(std::function<void()>&& func) {
    std::cout << "finally" << std::endl; 
    handle.promise().on_completed([func](auto result) {
      func(); 
    });
    return *this; 
  }

  explicit Task(std::coroutine_handle<promise_type> handle) noexcept: handle(handle) {}

  Task(Task&& task) noexcept: handle(std::exchange(task.handle, {})) {}

  Task(Task &) = delete;
  Task &operator=(Task &) = delete;

  ~Task() {
    if (handle) handle.destroy();
  }

  template<typename R>
  struct TaskAwaiter {
    // 当一个 Task 实例被 co_await 时，意味着它在 co_await 表达式返回之前已经执行完毕，
    // 当 co_await 表达式返回时，Task 的结果也就被取到，Task 实例在后续就没有意义了。
    // 因此 TaskAwaiter 的构造器当中接收 Task &&，防止 co_await 表达式之后继续对 Task 进行操作。
    explicit TaskAwaiter(Task<R> &&_task) noexcept 
      : task(std::move(_task)) {}

    TaskAwaiter(TaskAwaiter&& completion) noexcept 
      : task(std::exchange(completion.task, {})) {}

    TaskAwaiter(TaskAwaiter&) = delete; 
    TaskAwaiter& operator=(TaskAwaiter&) = delete; 

    constexpr bool await_ready() const noexcept {
      std::cout << "await_ready" << std::endl; 
      return false; 
    }

    void await_suspend(std::coroutine_handle<> handle) noexcept {
      std::cout << "await_suspend" << std::endl; 
      task.finally([handle]() {
        handle.resume(); 
      });
    }

    R await_resume() noexcept {
      std::cout << "await_resume" << std::endl; 
      return task.get_result(); 
    }

   private:
    Task<R> task; 
  };

  template<typename R> 
  struct TaskPromise {
    // 直接执行
    std::suspend_never initial_suspend() { Print(2) return {}; }
    // 执行完毕后挂起
    std::suspend_always final_suspend() noexcept { Print(4) return {}; }
    // 协程的返回值对象
    Task<R> get_return_object() {
      Print(1)
      return Task{ std::coroutine_handle<TaskPromise>::from_promise(*this) }; 
    }

    // co_await 支持
    template<typename _ResultType>
    TaskAwaiter<_ResultType> await_transform(Task<_ResultType> &&task) {
      std::cout << "get in await_transform" << std::endl; 

      return TaskAwaiter<_ResultType>(std::move(task)); 
    }

    void unhandled_exception() {
      std::lock_guard<std::mutex> lk(completion_lock); 
      result = Result<R>(std::current_exception()); 
      // 通知 get_result 中的wait
      completion.notify_all(); 
      // 调用回调
      notify_callbacks(); 
    }

    // co_yield 支持
    void return_value(R value) {
      Print(3)
      std::lock_guard<std::mutex> lk(completion_lock); 
      result = Result<R>(std::move(value)); 
      completion.notify_all(); 
      // 调用回调
      notify_callbacks(); 
    }
    
    void on_completed(std::function<void(Result<R>)>&& func) {
      std::cout << "get in on_completed" << std::endl; 
      std::unique_lock lock(completion_lock); 
      if (result.has_value()) {
        std::cout << "invoke" << std::endl; 
        auto value = result.value(); 
        lock.unlock(); 
        func(value); 
      } else {
        // 添加回调
        std::cout << "push_back callback list" << std::endl; 
        completion_callbacks.push_back(func); 
      }
    }

    ResultType get_result() {
      std::unique_lock<std::mutex> lk(completion_lock); 
      if (!result.has_value()) {
        completion.wait(lk); 
      }
      return result->get_or_throw();  
    }

   private: 
    std::optional<Result<R>> result; 
    std::mutex completion_lock; 
    std::condition_variable completion; 

    // 回调列表, 我们允许对同一个 Task 添加多个回调
    std::list<std::function<void(Result<R>)>> completion_callbacks; 

    void notify_callbacks() {
      auto value = result.value(); 
      for (auto &callback: completion_callbacks) {
        callback(value); 
      }
      completion_callbacks.clear(); 
    }
  };

 private:
  std::coroutine_handle<promise_type> handle; 
}; 


Task<int> simple_task2() {
  // debug("task 2 start ...");
  std::cout << "get in task2" << std::endl; 
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(1s);
  // debug("task 2 returns after 1s.");
  co_return 2;
}

Task<int> simple_task3() {
  // debug("in task 3 start ...");
  std::cout << "get in task3" << std::endl; 
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(2s);
  // debug("task 3 returns after 2s.");
  co_return 3;
}

Task<int> simple_task() {
  // debug("task start ...");
  std::cout << "get in task" << std::endl; 
  auto result2 = co_await simple_task2();
  // debug("returns from task2: ", result2);
  auto result3 = co_await simple_task3();
  // debug("returns from task3: ", result3);
  co_return 1 + result2 + result3;
}

int main() {
  auto simpleTask = simple_task();
  simpleTask.then([](int i) {
    // debug("simple task end: ", i);
    std::cout << i << std::endl; 
  }).catching([](std::exception &e) {
    std::cout << e.what() << std::endl; 
    // debug("error occurred", e.what());
  });

  // try {
  //   auto i = simpleTask.get_result();
  //   // debug("simple task end from get: ", i);
  // } catch (std::exception &e) {
  //   // debug("error: ", e.what());
  // }
  return 0;
}



#endif