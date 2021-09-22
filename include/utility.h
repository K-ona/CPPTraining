#pragma once

// std::swap()
#include <utility>

// getchar()
#include <stdio.h>

namespace KonaImpl {

using ll = long long;

// 快速排序所用划分函数
template <class RandomAccessIterator>
inline RandomAccessIterator partition(RandomAccessIterator first,
                                      RandomAccessIterator end) {
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

// 整数快读, 数字前**紧挨着**的符号视为负数
template <class Val_T>
inline void read(Val_T& r) {
  r = 0;
  bool sig = true;
  char ch = getchar();
  while (ch < '0' || ch > '9')
    sig = ch == '-' ? 0 : 1, ch = getchar();
  while (ch >= '0' && ch <= '9')
    r = (r << 1) + (r << 3) + (ch ^ 48), ch = getchar();
  r = sig ? r : -r;
}

// 整数快写
template <class Val_T>
inline void write(Val_T x, char end = ' ') {
  static char buf[20];
  static int len = -1;
  if (x < 0)
    putchar('-'), x = -x;
  do
    buf[++len] = x % 10, x /= 10;
  while (x);
  while (len >= 0)
    putchar(buf[len--] + '0');
  putchar(end);
}

// 与std::max相同
template<class Val_T>
inline const Val_T& max(const Val_T &a, const Val_T &b) {
  return  a < b ? b : a;
}

// 与std::min相同
template<class Val_T>
inline const Val_T& min(const Val_T &a, const Val_T &b) {
  return  a < b ? a : b;
}

}  // namespace KonaImpl
