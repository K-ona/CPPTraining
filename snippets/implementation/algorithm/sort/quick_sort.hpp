// created by Kona @VSCode
#include "../../../../include/utility.hpp"

// 快速排序
namespace KonaImpl {

// 快速排序所用划分函数
template <class RandomAccessIterator>
inline RandomAccessIterator partition(RandomAccessIterator first,
                                      RandomAccessIterator end) {
  auto x = --end;
  auto lf = first;
  for (auto it = first; it != x; ++it) {
    if (*it <= *x) {
      swap(*it, *(lf++));
    }
  }
  swap(*x, *lf);
  return lf;
}

// 针对RandomAccessIterator, 默认元素之间可以比大小
template <typename RandomAccessIterator>
inline void quick_sort(RandomAccessIterator first, RandomAccessIterator end) {
  using ptr = RandomAccessIterator;
  if (first != end) {
    ptr p = KonaImpl::partition(first, end); 
    quick_sort(first, p); 
    quick_sort(p + 1, end); 
  }
}

} // namespace KonaImpl