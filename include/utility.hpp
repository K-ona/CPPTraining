#pragma once

#include "mystlconfig.hpp"

// getchar()
#include <stdio.h>

namespace KonaImpl {

// 整数快读, 数字前**紧挨着**的符号视为负数
template <typename Val_T>
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
template <typename Val_T>
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
template<typename Val_T>
inline const Val_T& max(const Val_T &a, const Val_T &b) {
  return  a < b ? b : a;
}

// 与std::min相同
template<typename Val_T>
inline const Val_T& min(const Val_T &a, const Val_T &b) {
  return  a < b ? a : b;
}

// 交换元素
template< typename T>
constexpr void swap( T& a, T& b ) {
  T tmp = a; 
  a = b; 
  b = tmp; 
}

// 交换数组
template< typename T, size_t N>
constexpr void swap( T (&a)[N], T (&b)[N]) {
  for (size_t i = 0; i < N; ++i) {
    swap(a[i], b[i]); 
  }
}

}  // namespace KonaImpl
