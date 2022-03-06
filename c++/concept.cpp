#include <iostream>
#include <concepts>


// 在使用模板的时候, 我们经常需要想做一些限定. 比如需要一个类是整型等. 
// C++20 就给了一个这样限定的工具, concept 就是一个限制

/******************************************************************/
// concept的用法（来自https://zhuanlan.zhihu.com/p/107610017）

// 定义一个concept
template<typename T>
concept Integral = std::is_integral_v<T>;


// 用法1，用auto表明前面的是一个concept
Integral auto Add(Integral auto a, Integral auto b)
{
    return a + b;
}

// 用法2，用requires说明该模板需满足的concept
// template<typename T> 
// requires Integral<T>
// T Add(T a, T b)
// {
//     return a + b;
// }

// 用法3，与用法2类似，位置不同
// template<typename T>
// T Add(T a, T b) requires Integral<T>
// {
//     return a + b;
// }

// 用法4，直接将concept放入模板参数前
// template<Integral T>
// T Add(T a, T b)
// {
//     return a + b;
// }

/******************************************************************/
// concept的定义（来自https://zhuanlan.zhihu.com/p/351074390）

template<typename T> 
class S {}; 

template<typename T> 
concept C = std::is_integral_v<T>; 

// 使用requires可以提下面的要求
template <typename T>
concept R = requires(T a, T b)
{
    a + b;            // 需要 a + b 是有效的表达式
    typename T::type; // 需要 T::type 是有效的类型名
    S<T>();    // 需要模板类 S<T> 成功实例化
    C<T>;             // 需要满足 concept C<T>
};

template<typename T>
requires R<T>
void func(T val) {
  std::cout << "Get In\n"; 
}

// 也可以提这样的要求
// template <typename T>
// concept R = requires(T a, T b)
// {
//     {a + b} -> C;  // C是一个concept
//     // 等价于
//     a + b; 
//     C<decltype<a + b>>;
// };

// concept 之间可以做逻辑运算, 比如这样
// template<typename T> concept C = R<T> && S<T> && (W<T> || Z<T>);


int main() {
  
  // std::cout << Add(1.2, 2.2) << std::endl; 
  // Integral auto c = Add(1, 2); 
  std::cout << Add(1, 2) << std::endl; 

  // func(1); 

  return 0; 
}