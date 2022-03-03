#include "../../../../include/utility.hpp"

// 数据结构-堆
namespace KonaImpl {

// 使节点current为根节点的子树成为最大堆，假定子节点已满足最大堆的性质
template <typename RandomAccessIterator, typename Compare>
inline void max_heap(RandomAccessIterator current, KonaImpl::size_t pos, const RandomAccessIterator& last, Compare&& _cmp) {
  using ptr = RandomAccessIterator;
  ptr left = current + pos + 1; 
  ptr right = current + pos + 2; 
  ptr _max_element = current; 

  if (left < last and _cmp(*_max_element,  *left)) {
    _max_element = left; 
  }
  if (right < last and _cmp(*_max_element, *right)) {
    _max_element = right; 
  }
  
  if (_max_element != current) {
    swap(*current, *_max_element); 
    max_heap(_max_element, _max_element - current + pos, last, _cmp); 
  }
}

// 将[first, end)构造成最大堆
template <typename RandomAccessIterator, typename Compare>
inline void make_heap(RandomAccessIterator first, RandomAccessIterator end, 
                      Compare&& _cmp) {
  using ptr = RandomAccessIterator; 
  // static_assert(first < end);
  KonaImpl::size_t pos = static_cast<KonaImpl::size_t>((end - first) / 2); 
  while (pos-- != 0) {
    max_heap(first + pos, pos, end, std::forward<Compare>(_cmp));
  }
}

// 实施堆排序，针对RandomAccessIterator
template <typename RandomAccessIterator, typename Compare>
inline void heap_sort(RandomAccessIterator first, RandomAccessIterator end, Compare&& _cmp) {
  using ptr = RandomAccessIterator;
  KonaImpl::make_heap(first, end, std::forward<Compare>(_cmp)); 
  while (1 < end - first) {
    swap(*first, *--end); 
    max_heap(first, 0, end, std::forward<Compare>(_cmp)); 
  }
}

} // namespace KonaImpl