// created by Kona @VSCode
// rule 4: 查看型别推导结果

// 1. 通过ide查看
const int ci = 0; 
auto x = ci; 
auto y = &ci; 

// 2. 通过编译器诊断信息
template<typename T> 
class TD;

// error: aggregate 'TD<int> xType' has incomplete type and cannot be defined
// TD<decltype(x)> xType; 
// error: aggregate 'TD<const int*> yType' has incomplete type and cannot be defined
// TD<decltype(y)> yType;

#include <iostream>
#include <typeinfo>
#include <boost/type_index.hpp>

int main() {
  // 3. 运行时输出
  std::cout << typeid(x).name() << std::endl; 
  std::cout << typeid(y).name() << std::endl; 

  // template<>ty

  return 0; 
}
