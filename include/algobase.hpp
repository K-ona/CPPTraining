#pragma once

#include "algobase.hpp"
#include "utility.hpp"

namespace KonaImpl {
  
  template<typename Iterator1, typename Iterator2>
  bool range_equal(Iterator1 first, Iterator1 last, Iterator2 other) {
    while (first != last) {
      if (*first++ != *other++) 
        return false; 
    }
    return true; 
  }


};
