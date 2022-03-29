#pragma once

#include "algobase.hpp"
#include "function.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include "utility.hpp"

// std::is_same_v
#include <type_traits>

namespace KonaImpl {

template <typename Iterator1,
          typename Iterator2,
          typename Equal = equal_to<typename iterator_traits<Iterator1>::value_type>>
requires requires(Iterator1 _it1, Iterator2 _it2, Equal eq) {
  _it1++;
  _it2++;
}
bool range_equal(Iterator1 first,
                 Iterator1 last,
                 Iterator2 other,
                 Equal eq = {}) {
  if (std::is_same_v<Iterator1, Iterator2> and first == other) {
    return true;
  }
  while (first != last) {
    if (!eq(*first++, *other++))
      return false;
  }
  return true;
}

};  // namespace KonaImpl
