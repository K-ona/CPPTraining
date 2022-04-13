#pragma once

#include "mystlconfig.hpp"
#include "utility.hpp"
#include "..\snippets\implementation\container\vector.hpp"

namespace KonaImpl {

template<typename T>
class allocator {
 public:
  using value_type = T;
  using pointer = T*;
  using const_pointer = const T*;
  using size_t = KonaImpl::size_t;
  using ptrdiff_t = KonaImpl::ptrdiff_t;
  using vector = KonaImpl::vector;

  allocator() = default; 

  allocator(const allocator&) = delete; 
  allocator& operator=(const allocator&) = delete;

  allocate(size_t n) {
    return static_cast<pointer>(::operator new(n * sizeof(T)));
  }

  deallocate(pointer p, size_t n) {
    ::operator delete(p);
  }
  
};

};  // namespace KonaImpl
