// inline specifier
// https://en.cppreference.com/w/cpp/language/inline

// The inline specifier, when used in a function's decl-specifier-seq, 
// declares the function to be an inline function.
// A function defined entirely inside a class/struct/union definition, 
// whether it's a member function or a non-member friend function, is implicitly an inline function 
// if it is attached to the global module (since C++20).

// A function declared constexpr is implicitly an inline function.
// A deleted function is implicitly an inline function: 
// its (deleted) definition can appear in more than one translation unit.
// (since C++11)


// The inline specifier, when used in a decl-specifier-seq of a variable with static storage duration
//  (static class member or namespace-scope variable), declares the variable to be an inline variable.
// A static member variable (but not a namespace-scope variable) declared constexpr is implicitly an inline variable.
// (since C++17)

/*************************************************************************************/
// Explanation

// An inline function or inline variable (since C++17) has the following properties:

// 1. The definition of an inline function or variable (since C++17) must be reachable in the translation unit where it is accessed (not necessarily before the point of access).
// 2. An inline function or variable (since C++17) with external linkage (e.g. not declared static) 
// has the following additional properties:
//    1. There may be more than one definition of an inline function or variable (since C++17) in the program 
//  as long as each definition appears in a different translation unit and 
//  (for non-static inline functions and variables (since C++17)) all definitions are identical. 
//  For example, an inline function or an inline variable (since C++17) may be defined in a header file 
//  that is #include'd in multiple source files.
//    2. It must be declared inline in every translation unit.
//    3. It has the same address in every translation unit.
//   即inline标识的函数的定义可以在多个内存单元中并存，都有inline标识并且定义相同，则它们指的是同一个函数
//   对于inline变量则指的是同一个变量，它们具有相同的地址

// 在一个inline函数中，函数的局部静态变量被所有翻译单元所共享，它们指向同一个对象
// inline的原始意图是用做优化器的一个提示，即使用内联而不是函数调用
// 这避免了函数调用（传递参数和回收结果）产生的开销，但它可能会导致更大的可执行文件，因为该函数的代码重复了多次。
// 由于关键字 inline 的这种含义是不具约束力的，编译器可以自由地对任何未标记为 inline 的函数使用内联替换，
// 也可以自由地生成对任何标记为 inline 的函数的函数调用。
// 注:::这些优化选择不会改变上面列出的关于多个定义和共享静态的规则。

// Because the meaning of the keyword inline for functions came to mean "multiple definitions are permitted" 
// rather than "inlining is preferred", that meaning was extended to variables.
// (since C++17)

/*************************************************************************************/
// Notes
// 1. 如果具有外部链接的内联函数或变量 (C++17 起) 在不同的翻译单元中定义不同，则行为未定义
// 2. inline 说明符不能与块范围内（另一个函数内）的函数或变量（C++17 起）声明一起使用
// 3. inline 说明符不能将已在翻译单元中定义为非内联的函数或变量（C++17 起）重新声明。
// 4. If an inline function is declared in different translation units, the accumulated sets of default arguments must be the same at the end of each translation unit.
// 5. The implicitly-generated member functions and any member function declared as defaulted on its first declaration are inline just like any other function defined inside a class definition.
// 6. 有可能被多个文件所include的函数必须声明为inline否则会有链接错误


#include <iostream>

int main() {
  
  // inline int x; //error: 'inline' specifier invalid for variable 'x' declared at block scope

  inline void fun();

  return 0; 
}
