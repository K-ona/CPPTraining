// created by Kona @VSCode
// rule 2: 理解auto型别推导

// auto与模板函数参数型别推导类似，auto类似于typename T，型别饰词类似于Paramtype
// 同样分为三种情况
// 情况1：型别修饰词是指针或引用
// 情况2：型别修饰词是万能引用
// 情况3：型别修饰词既非指针也非引用

// 对于数组和函数名同样类似
const char name[] = "kona"; 
auto sp = name; // const char *sp
auto &rsp = name;  // const char (&rsp)[5]

void func(int, double){}; 
auto fp = func; // void (*fp)(int, double)
auto &rfp = func; // void (&rfp)(int, double)


#include <iostream>
#include <initializer_list>

using std::cout;
using std::endl;

// 特殊情况：列表初始化(为支持统一初始化)
// auto型别推导会假定大括号括起的表示式是一个initializer_list
// 而模板型别推导不会
// 初始化方式有：
int x1 = 27; // int 
int x2(27); // int 
int x3 = {27}; // int 
int x4{27}; // int 

// 采用auto
auto y1 = 27; // int 
auto y2(27); // int 
auto y3 = {27}; // std::initializer_list<int> 
auto y4{27}; // int

int main() {
  
/****************************************************************************************/

  // cout << y3 << endl; 
  cout << y4 << endl; 
  

  return 0; 
}