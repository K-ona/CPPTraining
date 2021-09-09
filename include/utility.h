#pragma once

// 用其中swap函数
#include <utility>

namespace KonaImpl{

template <class RandomAccessIterator>
inline RandomAccessIterator partition(RandomAccessIterator first, RandomAccessIterator end) {
  auto x = --end; 
  auto lf = first; 
  for (auto it = first; it != x; ++it) {
    if (*it <= *x) {
      std::swap(*it, *(lf++)); 
    }
  }
  std::swap(*x, *lf); 
  return lf; 
}


}  // namespace MySort
