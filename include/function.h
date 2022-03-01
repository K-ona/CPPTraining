#pragma once

namespace KonaImpl {

  // std::less
  template<typename T> 
  class less {
    inline bool operator()(const T& first, const T& second) {
      return first < second; 
    }
  };
  
  // std::greater
  template<typename T> 
  class greater {
    inline bool operator()(const T& first, const T& second) {
      return first > second; 
    }
  };
  
};
