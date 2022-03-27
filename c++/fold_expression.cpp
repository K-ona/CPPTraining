// fold expression(since C++17)

// 语法：
// ( pack op ... )	(1)	: unary right fold
// ( ... op pack )	(2)	: unary left fold
// ( pack op ... op init )	(3)	: binary right fold
// ( init op ... op pack )	(4)	: binary left fold
// ( pack op ... op ... op init )	(5)	: n-ary right fold

// op需属于下列32种类型：
// + - * / % ^ & | = < > << >> += -= *= /= %= ^= &= |= <<= >>= == != <= >= && || , .* ->*
// 在二元折叠时，左右的op需相同

// pack
// 一个表达式，它包含一个未扩展的参数包，并且不包含优先级低于顶层强制转换的运算符

// init
// 不包含未扩展参数包且不包含优先级低于顶层转换的运算符的表达式

// Explanation
// The instantiation of a fold expression expands the expression e as follows:

// 1) Unary right fold (E op ...) becomes (E1 op (... op (EN-1 op EN)))
// 2) Unary left fold (... op E) becomes (((E1 op E2) op ...) op EN)
// 3) Binary right fold (E op ... op I) becomes (E1 op (... op (EN−1 op (EN op I))))
// 4) Binary left fold (I op ... op E) becomes ((((I op E1) op E2) op ...) op EN)


#include <iostream>
#include <vector>
#include <climits>
#include <cstdint>
#include <type_traits>
#include <utility>
 
template<typename ...Args>
void printer(Args&&... args)
{
    (std::cout << ... << args) << '\n';
}

template<typename T, typename... Args>
void push_back_vec(std::vector<T>& v, Args&&... args)
{
    static_assert((std::is_constructible_v<T, Args&&> && ...));
    (v.push_back(std::forward<Args>(args)), ...);
}

// compile-time endianness swap based on http://stackoverflow.com/a/36937049 
template<class T, std::size_t... N>
constexpr T bswap_impl(T i, std::index_sequence<N...>)
{
    return (((i >> N*CHAR_BIT & std::uint8_t(-1)) << (sizeof(T)-1-N)*CHAR_BIT) | ...);
}

template<class T, class U = std::make_unsigned_t<T>>
constexpr U bswap(T i)
{
    return bswap_impl<U>(i, std::make_index_sequence<sizeof(T)>{});
}

int main()
{
    printer(1, 2, 3, "abc");
 
    std::vector<int> v;
    push_back_vec(v, 6, 2, 45, 12);
    push_back_vec(v, 1, 2, 9);
    for (int i : v) std::cout << i << ' ';
 
    static_assert(bswap<std::uint16_t>(0x1234u)==0x3412u);
    static_assert(bswap<std::uint64_t>(0x0123456789abcdefULL)==0xefcdab8967452301ULL);
}