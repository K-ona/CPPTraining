#include "../../../include/utility.hpp"
#include "../../../include/exception.hpp"
#include "../../../include/debug.hpp"


#include <iostream>
#define DEBUG_MODE

// vector
namespace KonaImpl {

template<typename T>
class vector {
  #define VECTOR_CONSTRUCT(n) (n > 64 ? (end_ = data_ = new T[n], cap_ = data_ + n) : \
                                     (end_ = data_ = new T[64], cap_ = data_ + 64))
 public: 
  using size_t = KonaImpl::size_t;
  using ptrdiff_t = KonaImpl::ptrdiff_t;
  using value_type = T;
  using pointer = value_type*;
  using const_pointer = const value_type*;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = value_type*;
  using const_iterator = const value_type*;

  // constructors
  vector() : data_(nullptr), end_(nullptr), cap_(nullptr) {};  
  vector(size_t n, const T& val = T()) {
    VECTOR_CONSTRUCT(n); 
    end_ = data_ + n;
    for (size_t i = 0; i < n; ++i) {
      data_[i] = val;
    }
  }

  vector(std::initializer_list<T> il) {
    size_t n = il.size(); 
    VECTOR_CONSTRUCT(n); 
    end_ = data_ + n;
    for (size_t i = 0; i < n; ++i) {
      data_[i] = il.begin()[i];
    }
  }

  const_iterator begin() const { return data_; }
  iterator begin() { return data_; }
  const_iterator end() const { return end_; }
  iterator end() { return end_; }

  
 protected: 
  T* data_; 
  T* end_; 
  T* cap_;
}; 
    

} // namespace KonaImpl
