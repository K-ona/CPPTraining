#pragma pack(push)  // 将当前pack设置压栈保存
#pragma pack(1)     // 必须在结构体定义之前使用
struct S1 {
  char c;
  int i;
};
struct S2 {
  char c1;
  S1 s;
  char c2;
};
// struct S1
// {
//       char c;
//       int i;
// }__attribute__ ((packed));

#pragma pack(pop)  // 恢复先前的pack设置

#pragma pack(4)  // 设置为4

struct T1 {
  char c;
  int i;
};

struct T2 {
  char c1;
  T1 s;
  char c2;
};

#include <iostream>

// #define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

using namespace std;

int main() {
  std::cout << "alignment of std::string = " << std::alignment_of_v<std::string> << std::endl;
  std::cout << "alignment of char = " << std::alignment_of_v<char> << std::endl;
  std::cout << "alignment of int = " << std::alignment_of_v<int> << std::endl; 
  std::cout << "alignment of double = " << std::alignment_of_v<double> << std::endl; 
  std::cout << "alignment of float = " << std::alignment_of_v<float> << std::endl; 
  std::cout << "alignment of long long = " << std::alignment_of_v<long long> << std::endl; 
  
  cout << sizeof(S1) << endl;
  std::cout << std::alignment_of<S1>::value << ' ';
  std::cout << std::alignment_of<S1>() << ' ';   // alt syntax
  std::cout << std::alignment_of_v<S1> << '\n';  // c++17 alt syntax
  cout << sizeof(S2) << endl;

  cout << sizeof(T1) << endl;
  std::cout << std::alignment_of<T1>::value << ' ';
  std::cout << std::alignment_of<T1>() << ' ';   // alt syntax
  std::cout << std::alignment_of_v<T1> << '\n';  // c++17 alt syntax

  cout << sizeof(T2) << endl;
  cout << offsetof(T2, s) << endl;
  cout << offsetof(T2, c2) << endl;
  return 0;
}