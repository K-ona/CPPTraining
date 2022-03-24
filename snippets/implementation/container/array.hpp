#include "../../../include/utility.hpp"
#include "../../../include/exception.hpp"


// 数组
namespace KonaImpl {

  template<typename Tp, KonaImpl::size_t N>
    class array {
     public:
      using size_t = KonaImpl::size_t; 
      using ptrdiff_t = KonaImpl::ptrdiff_t; 
      using value_type = Tp; 
      using pointer = value_type*; 
      using const_pointer = const value_type*; 
      using reference = value_type&; 
      using const_reference = const value_type&; 
      using iterator = value_type*; 
      using const_iterator = const value_type*; 

      constexpr reference operator[](size_t _n) noexcept {
        return m_data[_n]; 
      }

      constexpr const_reference operator[](size_t _n) const noexcept {
        return m_data[_n]; 
      }

      constexpr reference at(size_t _n)  {
        return _n < N ? m_data[_n] : (
          throw KonaImpl::out_of_range("array index is out of range!"),
                        m_data[0]);
      }

      constexpr const_reference at(size_t _n)  const {
        return _n < N ? m_data[_n] : (
          throw KonaImpl::out_of_range("array index is out of range!"),
                        m_data[0]);
      }

      size_t size() const {
        return N;
      }

      constexpr iterator begin() noexcept {
        return m_data; 
      }

      constexpr const_iterator begin() const noexcept {
        return m_data; 
      }

      constexpr iterator end() noexcept {
        return m_data + N; 
      }

      constexpr const_iterator end() const noexcept {
        return m_data + N; 
      }

      constexpr reference front() noexcept {
        return *m_data; 
      }

      constexpr const_reference front() const noexcept {
        return *m_data; 
      }

      constexpr reference back() noexcept {
        return N ? *(m_data + N - 1) : *end(); 
      }

      constexpr const_reference back() const noexcept {
        return N ? *(m_data + N - 1) : *end(); 
      }

     private:
      Tp m_data[N]; 
    };

    // operators 
    template<typename Tp, KonaImpl::size_t N>
    inline bool operator==(const KonaImpl::array<Tp, N>& first, const KonaImpl::array<Tp, N>& second) noexcept {
      return KonaImpl::range_equal(first.begin(), first.end(), second.begin()); 
    }

    

} // namespace KonaImpl
