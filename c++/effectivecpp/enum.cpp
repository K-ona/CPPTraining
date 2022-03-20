// created by Kona @VSCode
// rule 10: 优先选用限定作用域的枚举类型，而非不限作用域的枚举类型

// 一般来说，大括号会限定变量（名）的作用域，
// 而不限作用域的（unscoped）枚举类型就不适用该规则：
#define Unscoped

#ifdef Unscoped
enum Color {
  black, 
  white, 
  red
};  // black, white, red所在作用域与Color相同

// int red; // error: 'int red' redeclared as different kind of entity

// unscoped枚举类型可以隐式转换到整数，从而进一步转换到浮点数
// 在使用中可能出现与枚举类型的本意完全不一样的用法



#endif

#ifndef Unscoped
// C++11限定作用域的（scoped）枚举类型，也称枚举类

enum class Color {
  black, 
  white, 
  red
}; 

auto white = false; // ok

// Color c = white; // error: "bool" 类型的值不能用于初始化 "Color" 类型的实体
Color c = Color::white; // ok
auto x = Color::white; 

#endif



int main() {
  

  return 0; 
}