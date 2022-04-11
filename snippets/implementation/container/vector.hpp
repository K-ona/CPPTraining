#include "../../../include/utility.hpp"
#include "../../../include/exception.hpp"
#include "../../../include/debug.hpp"
#include "../../../include/algobase.hpp"


#include <iostream>
#define DEBUG_MODE

// vector
namespace KonaImpl {

template<typename T>
class vector {
  #define VECTOR_DEFAULT_CAPACITY 64
  #define VECTOR_CONSTRUCT(n) (n > VECTOR_DEFAULT_CAPACITY ? (end_ = data_ = static_cast<iterator>(operator new(n * sizeof(T))), cap_ = data_ + n) : \
                                        (end_ = data_ = static_cast<iterator>(operator new(VECTOR_DEFAULT_CAPACITY * sizeof(T))), cap_ = data_ + VECTOR_DEFAULT_CAPACITY))   \
                                     //
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
  using load_factor_type = float;

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

  template<typename InputIterator> 
  requires requires (InputIterator it) {
    typename KonaImpl::iterator_traits<InputIterator>::value_type;
  }
  vector(InputIterator first, InputIterator last) {
    size_t n = KonaImpl::distance(first, last);
    VECTOR_CONSTRUCT(n); 
    end_ = data_ + n;
    for (size_t i = 0; i < n; ++i) {
      data_[i] = *(first + i);
    }
  }

  // copy constructor
  vector(const vector& v) {
    size_t n = v.size();
    VECTOR_CONSTRUCT(n);
    end_ = data_ + n;
    for (size_t i = 0; i < n; ++i) {
      data_[i] = v[i];
    }
  }

  // move constructor
  vector(vector&& v) noexcept {
    data_ = v.data_;
    end_ = v.end_;
    cap_ = v.cap_;
    v.data_ = nullptr;
    v.end_ = nullptr;
    v.cap_ = nullptr;
  }
  // destructor
  ~vector() {
    if (data_) {
      operator delete(data_);
    }
  }

  // iterator
  const_iterator begin() const { return static_cast<const_iterator>(data_); }
  const_iterator cbegin() const { return static_cast<const_iterator>(data_); }
  iterator begin() { return data_; }

  const_iterator end() const { return static_cast<const_iterator>(end_); }
  const_iterator cend() const { return static_cast<const_iterator>(end_); }
  iterator end() { return end_; }
  
  // size && capacity
  size_t size() const { return end_ - data_; }
  size_t capacity() const { return cap_ - data_; }

  // element access
  const_reference operator[](size_t n) const { return data_[n]; }
  reference operator[](size_t n) { return data_[n]; }

  const_reference at(size_t n) const {
    if (n >= size()) {
      throw KonaImpl::out_of_range("vector index is out of range!");
      return data_[0];
    }
    return data_[n];
  }
  reference at(size_t n) {
    if (n >= size()) {
      throw KonaImpl::out_of_range("vector index is out of range!");
      return data_[0];
    }
    return data_[n];
  }

  const_reference front() const { return *data_; }
  reference front() { return *data_; }

  const_reference back() const { return *(--end_); }
  reference back() { return *(--end_); }

  const_pointer data() const { return data_; }
  pointer data() { return data_; }

  // modifiers
  void push_back(const T& val) {
    reallocate_expand();
    *(end_++) = val;
  }

  void push_back(T&& val) {
    reallocate_expand();
    *(end_++) = val;
  }

  void pop_back() {
    if (end_ == data_) {
      throw KonaImpl::out_of_range("vector is empty!");
    }
    reallocate_shrink(); 
    --end_;
  }

  void resize(size_t n, value_type val = value_type()) {
    size_t sz = size(); 
    if (n > sz) {
      reallocate_expand(n - sz);
      for (size_t i = sz; i < n; ++i) {
        data_[i] = val;
      }
    } else if (n < sz) {
      reallocate_shrink(sz - n);
    }
    end_ = data_ + n;
  }

  void reserve(size_t n) {
    size_t sz = size(); 
    if (sz < n) {
      reallocate_expand(n - sz);
    }
  }

 protected:
  void reallocate_expand(size_t add_items = 1) {
    if (end_ + add_items <= cap_) { return; }
    static_assert(load_factor > 1, "load factor must be greater than 1!");

    size_t sz = size();
    // empty vector and expanded vector with capacity less than VECTOR_DEFAULT_CAPACITY
    if (!sz and add_items < VECTOR_DEFAULT_CAPACITY) {
      VECTOR_CONSTRUCT(VECTOR_DEFAULT_CAPACITY); 
      return ;
    }

    size_t new_cap = max(static_cast<size_t>(VECTOR_DEFAULT_CAPACITY), capacity());
    while (sz + add_items > new_cap) {
      new_cap *= load_factor;
    }
    iterator new_data = static_cast<iterator>(operator new(new_cap * sizeof(T)));
    memcpy(new_data, data_, sz * sizeof(T));
    operator delete(data_); 
    data_ = new_data;
    end_ = data_ + sz;
    cap_ = data_ + new_cap;
  }

  void reallocate_shrink(size_t sub_items = 1) {
    size_t sz = size(); 
    size_t cap = capacity();
    static_assert(load_factor > 1, "load factor must be greater than 1!"); 
    // get the new capacity
    while (sz - sub_items < cap / (1 + load_factor)) {
      cap /= load_factor;
    }

    cap = max(cap, static_cast<size_t>(VECTOR_DEFAULT_CAPACITY));
    if (cap == capacity()) { return; }
    iterator new_data = static_cast<iterator>(operator new(cap * sizeof(T))); 
    memcpy(new_data, data_, sz * sizeof(T));

    operator delete(data_); 
    data_ = new_data;
    end_ = data_ + sz;
    cap_ = data_ + cap;
  }

 public:
  vector& operator=(const vector& v) {
    if (this == &v) { return *this; }
    size_t n = v.size();
    VECTOR_CONSTRUCT(n);
    memcpy(data_, v.data(), n * sizeof(T));
    return *this;
  }

  vector& operator=(vector&& v) noexcept {
    if (this == &v) { return *this; }
    data_ = v.data_;
    end_ = v.end_;
    cap_ = v.cap_;
    v.data_ = nullptr;
    v.end_ = nullptr;
    v.cap_ = nullptr;
    return *this;
  }

  bool operator==(const vector& v) const {
    if (size() != v.size()) { return false; }
    for (size_t i = 0; i < size(); ++i) {
      if (data_[i] != v.data_[i]) { return false; }
    }
    return true;
  }

  bool operator!=(const vector& v) const {
    return !(*this == v);
  }

  bool operator<(const vector& v) const {
    return lexicographical_less(begin(), end(), v.begin(), v.end());
  }
  
 protected: 
  T* data_; 
  T* end_; 
  T* cap_;
  static constexpr load_factor_type load_factor = 2.0;
}; 
    
template<>
class vector<bool> {
 public: 
  vector() = delete; 
  vector(size_t n, const bool& val = bool()) = delete;
}; 

} // namespace KonaImpl
