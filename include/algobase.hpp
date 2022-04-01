#pragma once

#include "algobase.hpp"
#include "function.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include "utility.hpp"

// std::is_same_v
#include <type_traits>

namespace KonaImpl {

/**
 *  @brief Finds the first position in which @p val could be inserted
 *         without changing the ordering.
 *  @param  first   Begin iterator of a range.
 *  @param  last    End iterator of a range.
 *  @param  other   Begin iterator of another range.
 *  @param  eq    A functor to use for equivalent.
 *  @return A boolean denoting whether the two ranges are equivalent.
 *
*/
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

/**
 *  @brief Finds the first position in which @p val could be inserted
 *         without changing the ordering.
 *  @param  first   An iterator.
 *  @param  last    Another iterator.
 *  @param  val     The search term.
 *  @param  cmp    A functor to use for comparisons.
 *  @return An iterator pointing to the first element not less
 *           than @p val, or end() if every element is less
 *           than @p val.
 *
*/
template <std::random_access_iterator Iterator, 
          typename T, 
          typename Compare = KonaImpl::less<typename iterator_traits<Iterator>::value_type>>
Iterator lower_bound(Iterator first, Iterator last, T val, Compare cmp = {}) {
  while (first != last) {
    auto mid = first + (last - first) / 2;
    if (cmp(*mid, val)) {
      first = mid + 1;
    } else {
      last = mid;
    }
  }
  return first;
}


/**
 *  @brief Finds the last position in which @p val could be inserted
 *         without changing the ordering.
 *  @param  first   An iterator.
 *  @param  last    Another iterator.
 *  @param  val     The search term.
 *  @param  cmp    A functor to use for comparisons.
 *  @return An iterator pointing to the first element greater
 *           than @p val, or end() if no elements is greater than @p val.
 *
*/
template <std::random_access_iterator Iterator, 
          typename T, 
          typename Compare = KonaImpl::less<typename iterator_traits<Iterator>::value_type>>
Iterator upper_bound(Iterator first, Iterator last, T val, Compare cmp = {}) {
  while (first != last) {
    auto mid = first + (last - first) / 2;
    if (cmp(val, *mid)) {
      last = mid;
    } else {
      first = mid + 1;
    }
  }
  return first;
}

};  // namespace KonaImpl
