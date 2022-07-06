#include "lock_free_queue.hpp"
#include <thread>
#include <iostream>
#include <vector>
#include <future>
#include <algorithm>
#include <queue>
#include <deque>
#include <bits/stl_numeric.h>

class join_threads {
  std::vector<std::thread>& threads;
 public:
  explicit join_threads(std::vector<std::thread>& threads_)
      : threads(threads_) {}
  ~join_threads() {
    for (unsigned long i = 0; i < threads.size(); ++i) {
      if (threads[i].joinable())
        threads[i].join();
    }
  }
};


class function_wrapper {
  struct impl_base {
    virtual void call() = 0; 
    virtual ~impl_base() {} 
  }; 

  std::unique_ptr<impl_base> impl; 
  template<typename F>
  struct impl_type: impl_base {
      F f; 
      impl_type(F&& f_): f(std::move(_f)) {}
      void call() { f(); }
  };

 public: 
  template<typename F>
  function_wrapper(F&& f): impl(new impl_type<F>(std::move(f))) {}

  void operator() () { impl->call(); }
  function_wrapper() = default; 
  function_wrapper(function_wrapper&& other) noexcept:
  impl(std::move(other.impl)) {}

  function_wrapper& operator= (function_wrapper&& other) {
    impl = std::move(other.impl); 
    return *this;
  }

  function_wrapper(const function_wrapper&) = delete; 
  function_wrapper(function_wrapper&) = delete; 
  function_wrapper& operator=(const function_wrapper&) = delete; 
}; 

class work_stealing_queue {
 private:
  using data_type = function_wrapper; 
  std::deque<data_type> the_queue; 
  mutable std::mutex the_mutex; 
 
 public:
  work_stealing_queue() {}
  work_stealing_queue(const work_stealing_queue& other) = delete; 
  work_stealing_queue& operator=(work_stealing_queue& other) = delete; 
  
  void push(data_type data) {
    std::lock_guard lock(the_mutex); 
    the_queue.push_front(std::move(data));
  }

  bool empty() const {
    std::lock_guard lock(the_mutex); 
    return the_queue.empty(); 
  }

  bool try_pop(data_type& res) {
    std::lock_guard lock(the_mutex); 
    if (the_queue.empty()) {
      return false; 
    }

    res = std::move(the_queue.front()); 
    the_queue.pop_front(); 
    return true;
  }

  bool try_steal(data_type& res) {
    std::lock_guard lock(the_mutex); 
    if (the_queue.empty()) {
      return false; 
    }
    res = std::move(the_queue.back()); 
    the_queue.pop_back(); 
    return true; 
  }
}; 

class thread_pool {
  std::atomic_bool done;
  // thread_safe_queue
  using task_type = function_wrapper; 
  lock_free_queue<task_type> work_queue;  // 1

  std::vector<std::unique_ptr<work_stealing_queue>> queues; 
  std::vector<std::thread> threads;                      // 2
  join_threads joiner;   

  static thread_local work_stealing_queue* local_work_queue; 
  static thread_local unsigned my_index; 
                                  // 3
  void worker_thread(unsigned my_index_) {
    my_index = my_index_; 
    local_work_queue = queues[my_index].get(); 
    while (!done) {
      run_pending_task(); 
    }
  }

  bool pop_task_from_local_queue(task_type& task) {
    return local_work_queue && local_work_queue->try_pop(task);
  }

  bool pop_task_from_pool_queue(task_type& task) {
    auto ptr = work_queue.pop(); 
    if (!ptr) return false; 
    task = std::move(*ptr); 
    return true;
  }

  bool pop_task_from_other_queue(task_type& task) {
    for (unsigned i = 0; i < queues.size(); ++i) {
      const unsigned index = (my_index + i + 1) % queues.size(); 
      if (queues[index]->try_steal(task)) {
        return true;
      }
    }
    return false; 
  }

 public:
  thread_pool() : done(false), joiner(threads) {
    unsigned const thread_count = std::thread::hardware_concurrency();  // 8
    try {
      for (unsigned i = 0; i < thread_count; ++i) {
        queues.push_back(std::unique_ptr<work_stealing_queue>(new work_stealing_queue)); 
        threads.push_back(std::thread(&thread_pool::worker_thread, this, i));  // 9
      }
    } catch (...) {
      done = true;  // 10
      throw;
    }
  }

  ~thread_pool() {
    done = true;  // 11
  }

  template <typename FunctionType>
  std::future<typename std::result_of_t<FunctionType()>> 
  submit(FunctionType f) {
    using result_type = typename std::result_of_t<FunctionType()>; 
    std::packaged_task<result_type()> task(std::move(f)); 
    std::future<result_type> res(task.get_future()); 
    if (local_work_queue) {
      local_work_queue->push(std::move(task)); 
    } else {
      work_queue.push(std::move(task));  // 12
    }
    return res; 
  }

  void run_pending_task() {
    task_type task; 
    if (pop_task_from_local_queue(task) || 
        pop_task_from_other_queue(task) || 
        pop_task_from_pool_queue(task)) {
      task(); 
    } else {
      std::this_thread::yield(); 
    }
  }

};

