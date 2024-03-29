// created by Kona @VSCode
// rule 2: 理解auto型别推导
// rule 5: 优先选用auto，而不是显式声明
// rule 6: 当auto推导的型别不符合要求时，使用带显式型别的初始化物习惯用法

// auto与模板函数参数型别推导类似，auto类似于typename T，型别饰词类似于Paramtype
// 同样分为三种情况
// 情况1：型别修饰词是指针或引用
// 情况2：型别修饰词是万能引用
// 情况3：型别修饰词既非指针也非引用

// 对于数组和函数名同样类似
const char name[] = "kona";
auto sp = name;    // const char *sp
auto& rsp = name;  // const char (&rsp)[5]

void func(int, double){};
auto fp = func;    // void (*fp)(int, double)
auto& rfp = func;  // void (&rfp)(int, double)

#include <initializer_list>
#include <iostream>
#include <memory>
#include <functional>
#include <map>
#include <unordered_map>

using std::cout;
using std::endl;

// 特殊情况：列表初始化(为支持统一初始化)
// auto型别推导会假定大括号括起的表示式是一个initializer_list
// 而模板型别推导不会
// 初始化方式有：
int x1 = 27;    // int
int x2(27);     // int
int x3 = {27};  // int
int x4{27};     // int

// 采用auto
auto y1 = 27;    // int
auto y2(27);     // int
auto y3 = {27};  // std::initializer_list<int>
auto y4{27};     // int

int main() {
  /****************************************************************************************/

  // 用auto声明闭包变量--c++11
  auto derefUPLess = [](const std::unique_ptr<int>& p1,
                        const std::unique_ptr<int>& p2) { return *p1 < *p2; };
  // --c++14
  auto derefLess = [](const auto& p1, const auto& p2) { return *p1 < *p2; };


  // std::function<int(int,int)> tmp;

  // 手动声明类型有误时可能导致的效率问题


  std::unordered_map<std::string, int> M; 
  // ...
  for (std::pair<std::string, int> x : M) { // 会导致复制，因为M的key为const std::string

  }

  // 隐形的代理类通常会给auto的使用带来麻烦
  // 如 std::vector<bool>::reference 

  std::vector<bool> V = {1, 0, 1, 1, 0, 1,}; 
  bool priority = V[5]; // 包含了隐式转换

  // 被推断成了 std::vector<bool>::reference 型别
  auto prio = V[5]; 

  // 解决方法，显式型别转换
  auto prio_r = static_cast<bool>(V[5]); 
  

  // 这种习惯用法不限于会产生代理型别的情况
  // 可以应用到想要强调你意在创建一个类型有别于初始化表达式型别的场合
  // 例：
  double calcEpsilon();
  auto ep = static_cast<float>(calcEpsilon());

  return 0;
}