#pragma once

#include "algobase.hpp"
#include "type_traits.hpp"
#include "utility.hpp"
#include "function.hpp"
#include "iterator.hpp"

#include <concepts>
#include <type_traits>

namespace KonaImpl {

template <typename Iterator1,
          typename Iterator2,
          typename Equal>
requires requires(Iterator1 _it1, Iterator2 _it2, Equal eq) {
  { eq(_it1, _it2) } -> std::__detail::__boolean_testable;
  *_it1;
  *_it2;
  eq(*_it1, *_it2);  // 可以比较
}
bool range_equal(Iterator1 first, Iterator1 last, Iterator2 other, Equal eq) {
  while (first != last) {
    if (!eq(*first++, *other++))
      return false;
  }
  return true;
}

};  // namespace KonaImpl
