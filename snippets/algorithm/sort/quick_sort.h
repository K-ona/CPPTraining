// created by Kona @VSCode
#include "../../../include/utility.h"
namespace KonaImpl {
namespace MySort {

// 针对RandomAccessIterator, 默认元素之间可以比大小
template <class RandomAccessIterator>
inline void quick_sort(RandomAccessIterator first, RandomAccessIterator end) {
  using ptr = RandomAccessIterator;
  if (first != end) {
    ptr p = KonaImpl::partition(first, end); 
    quick_sort(first, p); 
    quick_sort(p + 1, end); 
  }
}

}  // namespace MySort
} // namespace KonaImpl