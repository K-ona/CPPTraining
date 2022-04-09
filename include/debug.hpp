#pragma once

#include <string>
#include <iostream>

#ifdef DEBUG_MODE
template <typename T>
void DEBUG(T s) {
  std::cout << s << std::endl;
}

template<typename T, typename...Args>
void DEBUG(T t, Args...args) {
  std::cout << t << " ";
  DEBUG(args...);
}

#endif

#ifndef DEBUG_MODE
void DEBUG(std::string s) {
}
#endif