#include <future>
#include <vector>
#include <thread>
#include <iterator>

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

template<typename Iterator, typename MatchType>
Iterator parallel_find(Iterator first, Iterator last, MatchType match) {
  struct find_element {
    void operator() (Iterator begin, Iterator end, MatchType match, 
      std::promise<Iterator>& result, std::atomic<bool>* done) {
      try {
        for (; (begin != end) && !done->load(); ++begin) {
          if (*begin == match) {
            // 如果多线程同时找到匹配值或抛出异常，将会产生数据竞争。
            // 不过，这是良性的条件竞争，成功的竞争者会作为“第一个”返回线程。
            result->set_value(begin); 
            done->store(true); 
            return ;
          }
        }
      } catch (...) {
        try {
          result->set_exception(std::current_exception()); 
          done->store(true); 
        } catch (...) {  // 如果result对应promise已设置，可能会抛出一个异常，所以这里发生的任何异常都可以捕获并丢弃。

        }
      }
    }
  };

  unsigned const long length = std::distance(first, last); 
  if (!length) return last; 

  unsigned const long min_per_thread = 25;
  unsigned const long max_threads = (length + min_per_thread - 1) / min_per_thread; 

  unsigned const long hardware_threads = std::thread::hardware_concurrency(); 
  unsigned const long num_threads = std::min(hardware_threads ? hardware_threads : 2, max_threads); 

  unsigned const long block_size = length / num_threads; 

  std::promise<Iterator> result; 
  std::atomic<bool> done(false); 
  std::vector<std::thread> threads(num_threads - 1); 

  {
    join_threads joiner(threads); 

    Iterator block_start = first; 
    for (unsigned long i = 0; i < (num_threads - 1); ++i) {
      Iterator block_end = block_start; 
      std::advance(block_end, block_size); 
      threads[i] = std::thread(find_element(), block_start, block_end, &result, &done); 
      block_start = block_end; 
    }
    find_element(block_start, last, &result, &done); 
  } // 线程汇入

  if (!done.load()) {
    return last; 
  }

  return result.get_future().get(); 

}


// 使用 std::async 实现的并行find算法
// 假设使用硬件上所有可用的的线程，或使用其他机制对线程上的任务进行提前划分，可以使用 std::async，
// 以及递归数据划分的方式来简化实现(同时使用C++标准库中提供的自动缩放工具)。
// 使用 std::async 的parallel_find实现如下所示。

template<typename Iterator, typename MatchType>
Iterator parallel_find_impl(Iterator first, Iterator last, MatchType match, std::atomic<bool>& done) {
  try {
    unsigned const long length = std::distance(first, last); 
    unsigned const long min_per_thread = 25; 
    if (length < (2 * min_per_thread)) {
      for (; (first != last) && !done.load(); ++first) {
        if (*first == match) {
          done = true;
          return first; 
        }
      }
      return last;
    } else {
      Iterator const mid_point = first + length / 2;
      std::future<Iterator> async_result = std::async(&parallel_find_impl<Iterator, MatchType>, 
        mid_point, last, match, std::ref(done));
      
      Iterator const direct_result = parallel_find_impl(first, mid_point, match, done); 
      return direct_result == mid_point ? async_result.get() : direct_result; 
    }
  } catch (...) {
    done = true; 
    throw ;
  }
}

template<typename Iterator, typename MatchType>
Iterator parallel_find(Iterator first, Iterator last, MatchType match) {
  std::atomic<bool> done(false);
  return parallel_find_impl(first, last, match, done);
}