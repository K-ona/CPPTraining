#include "../../../include/exception.hpp"
#include "../../../include/utility.hpp"
#include "../../../include/algobase.hpp"

// 数组
namespace KonaImpl {

template <typename T, KonaImpl::size_t N>
class array {
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

  constexpr reference operator[](size_t _n) noexcept { return data[_n]; }

  constexpr const_reference operator[](size_t _n) const noexcept {
    return data[_n];
  }

  constexpr reference at(size_t _n) {
    return _n < N
               ? data[_n]
               : (throw KonaImpl::out_of_range("array index is out of range!"),
                  data[0]);
  }

  constexpr const_reference at(size_t _n) const {
    return _n < N
               ? data[_n]
               : (throw KonaImpl::out_of_range("array index is out of range!"),
                  data[0]);
  }

  size_t size() const { return N; }

  constexpr iterator begin() noexcept { return data; }

  constexpr const_iterator begin() const noexcept { return data; }

  constexpr iterator end() noexcept { return data + N; }

  constexpr const_iterator end() const noexcept { return data + N; }

  constexpr reference front() noexcept { return *data; }

  constexpr const_reference front() const noexcept { return *data; }

  constexpr reference back() noexcept { return N ? *(data + N - 1) : *end(); }

  constexpr const_reference back() const noexcept {
    return N ? *(data + N - 1) : *end();
  }

 // constructor
 public:

  array() = default;

  array(const array<T, N>& _a) {
    memcpy(data, _a.data, N * sizeof(T));
  }

  template <typename Tp, typename... Args>
  array(Tp first, Args&&... _args) {
    static_assert(sizeof...(Args) + 1 == N, "size of args is not equal to N");
    data[0] = first; 
    ptrdiff_t cnt = 0; 

    // fold expression (C++17)
    ( (data[++cnt] = std::forward<Args>(_args)), ... );
    // 作用相同 (C++11)
    // std::initializer_list<int>{ ((data[++cnt] = std::forward<Args>(_args)), 0)... };
  }

 private:
  T data[N];
};

// operators
template <typename T, KonaImpl::size_t N>
inline bool operator==(const KonaImpl::array<T, N>& first,
                       const KonaImpl::array<T, N>& second) noexcept {
  return KonaImpl::range_equal(first.begin(), first.end(), second.begin());
}

}  // namespace KonaImpl
