#pragma once

#ifdef DEBUG_MODE
#include "mystlconfig.hpp"
#include "iterator.hpp"
#include "debug.hpp"

// getchar()
#include <stdio.h>

#include <iterator>
#include <iostream>
#endif
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
template<typename T, size_t N>
constexpr void swap( T (&a)[N], T (&b)[N]) {
  for (size_t i = 0; i < N; ++i) {
    swap(a[i], b[i]); 
  }
}

// begin
template<typename Container>
requires requires(Container c) { c.begin(); }
constexpr decltype(auto) begin(Container& container) {
  return container.begin(); 
}

template<typename T, size_t N>
constexpr decltype(auto) begin(T (&array)[N]) {
  return array; 
}

// end
template<typename Container>
requires requires(Container c) { c.end(); }
constexpr decltype(auto) end(Container& container) {
  return container.end(); 
}

template<typename T, size_t N>
constexpr decltype(auto) end(T (&array)[N]) {
  return array + N; 
}

// sum
template<typename...Args> 
requires (sizeof...(Args) > 1)
constexpr decltype(auto) sum(Args&&...args) {
  // fold expression (C++17)
  return (... + args);
}

template<typename T> 
constexpr T sum(T&& arg) {
  return arg; 
}

constexpr decltype(auto) sum() {
  return 0;
}

template<typename Iterator>
requires requires(Iterator it) {
  typename Iterator::value_type;
  typename Iterator::difference_type;
  typename Iterator::pointer;
  typename Iterator::reference;
  typename Iterator::iterator_category;
} or requires(Iterator first, Iterator second) {
  *first;
  *first + *second;
} // 迭代器or指针
constexpr decltype(auto) sum(Iterator first, Iterator second) {
  typename std::iterator_traits<Iterator>::value_type res = {};
  for (; first != second; ++first) {
    res += *first;
  }
  return res;
}

template<typename Container>
requires requires(Container container) {
  begin(container); 
  end(container); 
} // 需为容器类型
constexpr decltype(auto) sum(Container&& container) {
  return sum(begin(container), end(container));
}

}  // namespace KonaImpl
