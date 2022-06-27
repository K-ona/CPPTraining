#include <thread>
#include <iostream>
#include <vector>
#include <future>
#include <algorithm>
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

// 分块做法
template<typename Iterator>
void parallel_partial_sum(Iterator first, Iterator last) {
  typedef typename Iterator::value_type value_type; 

  struct process_chunk {
    void operator() (Iterator begin, Iterator last, 
                     std::future<value_type>* previous_end_value,
                     std::promise<value_type>* end_value) {
      try
      {
        Iterator end = last;
        ++end; 
        std::partial_sum(begin, end, begin); 
        if (previous_end_value) {
          value_type& addend = previous_end_value->get();
          *last += addend; 
          if (end_value) {
            end_value->set_value(*last);
          }
          std::for_each(begin, last, [addend](value_type& item) {
            item += addend; 
          });
        } else {
          end_value->set_value(*last);
        }
      } catch(...) {
        if (end_value) {
          end_value->set_exception(std::current_exception()); 
        } else {
          throw; 
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

  std::vector<std::thread> threads(num_threads - 1); 
  std::vector<std::promise<value_type>> end_values(num_threads - 1); 
  std::vector<std::future<value_type>> previous_end_values; 
  previous_end_values.reserve(num_threads - 1); 

  join_threads(threads); 
  Iterator block_start = first;
  for (unsigned long i = 0; i < (num_threads - 1); ++i) {
    Iterator block_last = block_start; 
    std::advance(block_last, block_size - 1); 
    threads[i] = std::thread(parallel_partial_sum(), block_start, block_last, 
                             i ? &previous_end_values[i - 1] : nullptr, &end_values[i]); 
    block_start = block_last; 
    ++block_start; 
    previous_end_values.push_back(end_values[i].get_future()); 
  }

  Iterator final_element = block_start; 
  std::advance(final_element, std::distance(block_start, last) - 1); 
  process_chunk()(block_start, final_element, (num_threads > 1) ? &previous_end_values.back() : 0, nullptr);
}

