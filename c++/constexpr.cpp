// constexpr specifier (since C++11)

// constexpr - specifies that the value of a variable or function can appear in constant expressions

/*************************************************************************************/
// Explanation
// constexpr 说明符声明"可以"(不是必须)在编译时计算函数或变量的值
// 然后可以在仅允许编译时常量表达式的情况下使用此类变量和函数（前提是给出了适当的函数参数）
// 在对象声明或非静态成员函数（C++14 前）中使用的 constexpr 说明符暗示 const。
// 在函数或静态数据成员 (C++17 起) 声明中使用的 constexpr 说明符暗示inline。
// 如果函数或函数模板的任何声明具有 constexpr 说明符，则每个声明都必须包含该说明符。

// 一个constexpr变量必须满足：
// 1. 类型必须为字面类型
// 2. 必须立即初始化
// 3. 其初始化的完整表达式，包括所有隐式转换、构造函数调用等，必须是常量表达式
// 4. (c++20起) 它必须拥有常量析构，即： 它不是类类型亦或其（可能多维的）数组，或
//    它是类类型或其（可能多维的）数组，且该类类型拥有 constexpr 析构函数；
//    对于作用仅为销毁该对象的虚设表达式e ，如果该对象与其非 mutable 子对象
//   （但非其 mutable 子对象）的生存期始于 e 内，那么 e 是核心常量表达式。

// 一个constexpr函数必须满足：
// 1. 它不能是个虚函数（c++20前）
// 2. 它不能是个协程（c++20起）
// 3. 有返回类型的话只能是字面类型
// 4. 参数类型也必须是字面类型
// 5. 对于构造和析构函数，该类不能有虚基类
// 6. 

#include <iostream>
#include <stdexcept>
 
// C++11 constexpr functions use recursion rather than iteration
// (C++14 constexpr functions may use local variables and loops)
constexpr int factorial(int n)
{
    return n <= 1 ? 1 : (n * factorial(n - 1));
}
 
// literal class
class conststr {
    const char* p;
    std::size_t sz;
public:
    template<std::size_t N>
    constexpr conststr(const char(&a)[N]): p(a), sz(N - 1) {}
 
    // constexpr functions signal errors by throwing exceptions
    // in C++11, they must do so from the conditional operator ?:
    constexpr char operator[](std::size_t n) const
    {
        return n < sz ? p[n] : throw std::out_of_range("");
    }
    constexpr std::size_t size() const { return sz; }
};
 
// C++11 constexpr functions had to put everything in a single return statement
// (C++14 doesn't have that requirement)
constexpr std::size_t countlower(conststr s, std::size_t n = 0,
                                             std::size_t c = 0)
{
    return n == s.size() ? c :
           'a' <= s[n] && s[n] <= 'z' ? countlower(s, n + 1, c + 1) :
                                       countlower(s, n + 1, c);
}
 
// output function that requires a compile-time constant, for testing
template<int n>
struct constN
{
    constN() { std::cout << n << '\n'; }
};
 
int main()
{
    // int a = 6;
    // int b = factorial(a); 
    // constN<b> tmp;

    std::cout << "4! = " ;
    constN<factorial(4)> out1; // computed at compile time
 
    volatile int k = 8; // disallow optimization using volatile
    std::cout << k << "! = " << factorial(k) << '\n'; // computed at run time
 
    std::cout << "the number of lowercase letters in \"Hello, world!\" is ";
    constN<countlower("Hello, world!")> out2; // implicitly converted to conststr
}