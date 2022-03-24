#pragma once
// #include <functional>

namespace KonaImpl {

  // std::less
  template<typename T> 
  struct less {
    constexpr bool operator()(const T& first, const T& second) {
      return first < second; 
    }
  };
  
  // std::greater
  template<typename T> 
  struct greater {
    constexpr bool operator()(const T& first, const T& second) {
      return first > second; 
    }
  };
  
  template<typename T>
  struct equal
  {
    constexpr bool operator()(const T& x, const T& y) const
    { return x == y; }
  };
};
