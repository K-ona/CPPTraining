#pragma once

#include "mystlconfig.hpp"
#include "concepts.hpp"
#include "type_traits.hpp"

namespace KonaImpl {

/// reference: gcc_11.2.0\bits\stl_iterator_base_types.h

///  Marking input iterators.
struct input_iterator_tag { };

///  Marking output iterators.
struct output_iterator_tag { };

/// Forward iterators support a superset of input iterator operations.
struct forward_iterator_tag : public input_iterator_tag { };

/// Bidirectional iterators support a superset of forward iterator
/// operations.
struct bidirectional_iterator_tag : public forward_iterator_tag { };

/// Random-access iterators support a superset of bidirectional
/// iterator operations.
struct random_access_iterator_tag : public bidirectional_iterator_tag { };

/// Contiguous iterators point to objects stored contiguously in memory.
struct contiguous_iterator_tag : public random_access_iterator_tag { };

// 迭代器通用的 type traits
template <typename _Category,
          typename _Tp,
          typename _Distance = ptrdiff_t,
          typename _Pointer = _Tp*,
          typename _Reference = _Tp&>
struct iterator {
  typedef _Category iterator_category;
  /// The type "pointed to" by the iterator.
  typedef _Tp value_type;
  /// Distance between iterators is represented as this type.
  typedef _Distance difference_type;
  /// This type represents a pointer-to-value_type.
  typedef _Pointer pointer;
  /// This type represents a reference-to-value_type.
  typedef _Reference reference;
};


// 针对一般迭代器
template <typename Iterator>
struct iterator_traits {
  using iterator_category = typename Iterator::iterator_category;
  using value_type = remove_cv_t<typename Iterator::value_type>;
  using difference_type = typename Iterator::difference_type;
  using pointer = typename Iterator::pointer;
  using reference = typename Iterator::reference;
};

// 针对指针
template <typename T>
requires is_object_v<T>
struct iterator_traits<T*> {
  using iterator_concept = contiguous_iterator_tag;
  using iterator_category = random_access_iterator_tag;
  using value_type = remove_cv_t<T>;
  using difference_type = ptrdiff_t;
  using pointer = T*;
  using reference = T&;
};

};  // namespace KonaImpl
