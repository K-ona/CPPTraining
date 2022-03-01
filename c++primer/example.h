#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <atomic>

// function included in multiple source files must be inline
// 否则会有链接错误
inline int sum(int a, int b) {
  return a + b;
}

// variable with external linkage included in multiple source files must be
// inline
inline std::atomic<int> counter(0);

#endif