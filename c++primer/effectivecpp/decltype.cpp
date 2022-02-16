// created by Kona @VSCode
// rule 3: 理解decltype

// 与模板和auto相反，decltype通常返回是给定名字或表达式的确切类型

const int i = 0; // decltype(i): const int
decltype(i) j = i; 

bool f(const char* s); // decltype(f): bool (const char *)
                       // decltype(s): const char* s
decltype(f) g; // bool g(const char*)

struct O
{
  int x; // decltype(O::x): int
  double y; // decltype(O::y): double
};

// 主要用途在于声明返回值依赖于形参的函数模板
// 如许多容器的[]返回引用类型，有些容器[]返回对象

// version 1 (C++11)
template<typename Container, typename Index>
auto authAndAccess(Container& C, Index i) -> decltype(C[i]) { 
  // ...
  return C[i]; 
}

// version 2
// C++11允许对单表达式的lambda返回值进行推导
// C++14允许一切lambda和函数的返回值推导
template<typename Container, typename Index>
auto authAndAccess(Container& C, Index i) { // 若去掉尾序返回值，则返回值推导使用模板型别推导规则会忽略引用
  // ...
  return C[i]; 
}

// version 3 (C++14)
template<typename Container, typename Index>
decltype(auto) authAndAccess(Container& C, Index i) { // 加上decltype使用decltype的型别推导规则
  // ...
  return C[i]; 
}

// version 4 (C++14)
template<typename Container, typename Index>
decltype(auto) authAndAccess(Container&& C, Index i) { // 使用万能引用，使函数可以接受右值临时容器
  // ...
  return C[i]; 
}

// version 5 (C++14)
template<typename Container, typename Index>
decltype(auto) authAndAccess(Container&& C, Index i) { // 
  // ...
  return std::forward<Container>(C)[i]; 
}

// version 5 (C++11)
template<typename Container, typename Index>
auto authAndAccess(Container&& C, Index i) -> decltype(std::forward<Container>(C)[i]) {  
  // ...
  return std::forward<Container>(C)[i]; 
}

#include <vector>
std::vector<int> V{0, 1, 2, 3, 4, 5}; 
// decltype(V): std::vector<int>
// decltype(V[0]): int &

int main() {

  // 也常用于声明变量
  O oo; 
  const O& cro = oo; 
  auto so = cro; // so为O类型
  decltype(cro) so2 = so; // so2为const O&类型
  
  // 当decltype应用于非名字的左值表示式时，会保持推导类型为左值引用
  int x = 0; 
  // decltype(x): int
  // 而decltype( (X) ): int&
  

}