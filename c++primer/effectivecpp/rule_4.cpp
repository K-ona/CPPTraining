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

template<typename T>
void f(const T& para) {
  using std::cout;
  using boost::typeindex::type_id_with_cvr; 

  cout << "T = " << type_id_with_cvr<T>().pretty_name() << '\n'; 

  cout << "para = " << type_id_with_cvr<decltype(para)>().pretty_name() << '\n'; 

}

int main() {
  // 3. 运行时输出, 不保证正确
  std::cout << typeid(x).name() << std::endl; 
  std::cout << typeid(y).name() << std::endl; 

  // 4. boost库，保证正确
  f(1); 
  f(ci); 
  f(x); 
  f(y); 

  return 0; 
}
