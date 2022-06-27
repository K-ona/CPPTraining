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

template<typename Iterator, typename Func>
void parallel_for_each(Iterator first, Iterator last, Func f) {
  unsigned const long len = std::distance(first, last);

  if (!len) return ;

  unsigned const long min_per_thread = 25; 
  unsigned const long max_threads = (len + min_per_thread - 1) / min_per_thread; 

  unsigned const long hardware_threads = std::thread::hardware_concurrency(); 
  unsigned const long num_threads = std::min(hardware_threads ? hardware_threads : 2, max_threads); 

  unsigned const long block_size = len / num_threads; 

  std::vector<std::future<void>> futures(num_threads - 1); 
  std::vector<std::thread> threads(num_threads - 1); 
  
  join_threads joiner(threads); 

  Iterator block_start = first;
  for (unsigned long i = 0; i < num_threads - 1; ++i) {
    Iterator block_end = block_start; 
    std::advance(block_end, block_size); 
    std::packaged_task<void(void)> task{[=](){
      std::for_each(block_start, block_end, f); 
    }};

    futures[i] = task.get_future(); 
    threads[i] = std::thread(std::move(task)); 
    block_start = block_end; 
  }

  std::for_each(block_start, last, f); 
  for (unsigned long i = 0; i < num_threads - 1; ++i) {
    // 工作线程不需要返回值时，调用futures[i].get()只为了检索工作线程的异常。
    // 如果不想把异常传递出去，可以省略这一步。
    futures[i].get(); 
  }
}

// 基于 std::async
template<typename Iterator, typename Func>
void parallel_for_each(Iterator first, Iterator last, Func f) {
  unsigned const long len = std::distance(first, last);

  if (!len) return ;

  unsigned const long min_per_thread = 25; 
  if (len < 2 * min_per_thread) {
    std::for_each(first, last, f); 
  } else {
    const Iterator mid_point = first; 
    std::advance(mid_point, len / 2); 
    std::future<void> first_half = std::async(&parallel_for_each<Iterator, Func>, first, mid_point, f);
    parallel_for_each(mid_point, last, f); 
    first_half.get(); 
  }
}