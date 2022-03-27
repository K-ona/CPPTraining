#pragma once

#include "mystlconfig.hpp"

namespace KonaImpl {

// remove_cv
template <typename T>
struct remove_cv {
  using type = T;
};

template <typename T>
struct remove_cv<const T> {
  using type = T;
};

template <typename T>
struct remove_cv<volatile T> {
  using type = T;
};

template <typename T>
struct remove_cv<const volatile T> {
  using type = T;
};

// is_void
template<typename T> 
struct is_void {
  static constexpr bool value = false;
};

template<> 
struct is_void<void> {
  static constexpr bool value = true;
};

// is_reference
template<typename T> 
struct is_reference {
  static constexpr bool value = false; 
};

template<typename T> 
struct is_reference<T&> {
  static constexpr bool value = true; 
};

template<typename T> 
struct is_reference<T&&> {
  static constexpr bool value = true; 
};


template <typename T>
struct is_object {
  static constexpr bool value =
      !(is_void<T>::value || is_reference<T>::value);
};


template <typename T>
using remove_cv_t = remove_cv<T>::type;

template <typename T>
static constexpr bool is_reference_t = is_reference<T>::value;

};  // namespace KonaImpl
