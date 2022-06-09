// https://www.bennyhuo.com/book/cpp-coroutines/

#include <coroutine>
#include <chrono>
#include <thread>
#include <future>
#include <iostream>

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