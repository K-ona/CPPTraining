// created by Kona @VSCode
// rule 7: 在创建对象时注意区分{}和()

// c++的对象初始化方式
// 1. 使用小括号
int x(0); 
// 2. 使用等号
int y = 0; 
// 3. 使用大括号
int z{0}; 
// 4. 使用等号+大括号 通常等同于3，
int u = {0}; 


#include <iostream> 
#include <vector>
#include <atomic>

class Widget{
 public:
  Widget() { std::cout << "default constructor" << std::endl; }
  // Widget(std::initializer_list<long double>) { std::cout << "initializer_list constructor" << std::endl; }
  // Widget(std::initializer_list<bool>) { std::cout << "initializer_list constructor" << std::endl; }
  Widget(std::initializer_list<std::string>) { std::cout << "initializer_list constructor" << std::endl; }
  Widget(int _x , int _y = 0, double _z = 0): x(_x), y(_y), z(_z) { std::cout << "non-default constructor" << std::endl; }
  ~Widget() {}
  Widget(const Widget &) { std::cout << "assignment constructor" << std::endl; }
  Widget& operator= (const Widget&) { std::cout << "operator=" << std::endl; return *this; }
 
  operator float() const { std::cout << "enforced conversion" << std::endl; return z; }
 private:
  // c++11起同样支持对类中非静态成员指定初值
  int x{0}; // 支持大括号
  int y = 0; // 支持等号
  double z = .0; 
  // int z(0); // 不支持小括号
}; 



int main() {

  // 首先区分赋值与初始化（对于内置类型意义不大）
  Widget w1; // 调用的是默认构造函数
  Widget w2 = w1; // 非赋值，调用的是复制构造函数
  w1 = w2; // 非赋值，调用的是赋值operator=

  // c++11引入了统一初始化，其形式为大括号初始化
  // c++98就无法在创建容器时指定初始化元素
  // 例：
  std::vector<int> V{1, 3, 5}; 

  // 不可复制的对象（如std::atomic）可以采用大括号和小括号来进行初始化，却不能使用"="
  // 经c++20测试，等号初始化可以调用构造函数 atomic(__integral_type __i)

  std::atomic<int> ai1 {0}; 
  std::atomic<int> ai2 (0); 
  std::atomic<int> ai3 = 0; 


  // 大括号初始化的特性1：禁止内建型别进行隐式窄化型别转换
  // 经测试c++20下只是发出警告
  // 例：
  double x = 0, y = 1, z = 2;
  
  int sum1{x + y + z}; 
  std::cout << sum1 << std::endl; 

  int sum2(x + y + 1); 
  std::cout << sum2 << std::endl; 

  // 大括号初始化的特性2：对于最令人苦恼的解析语法免疫
  // 最令人苦恼的解析语法：任何能够解析成声明的都解析成声明，可能将构造对象解析成了声明一个函数
  // 例：
  Widget w3(10); // 调用构造函数
  Widget w4(); // 而该表示意在构造一个默认对象却被解析成了函数声明，经测试会发出歧义警告

  // 于是这种情况就可以调用大括号进行初始化
   Widget w5{};

  // 大括号初始化的缺陷
  // 源于大括号初始化物、std::initializer_list以及构造函数重载决议之间的纠结关系

  // 构造函数被调用时，如果形参中没有std::initializer_list型别，那小括号和大括号没有区别
  // 若有，则优先(优先级非常高)调用符合std::initializer_list版本，
  // 即使是普通情况下执行复制或移动的构造函数，甚至涉及几次类型转换
  // 即使选用std::initializer_list版本的构造函数会失败

  Widget w6(w5); //调用复制构造函数
  Widget w7{w5}; //使用大括号，调用了std::initializer_list版本的构造函数，首先将widget对象转换成float，再将float转换成long double
  
  // Widget w8{10, 10, 5.0}; // error: narrowing conversion of '10' from 'int' to 'bool' [-Wnarrowing]
                             // error: narrowing conversion of '5.0e+0f' from 'float' to 'bool' [-Wnarrowing] 
                             // 容器类型为bool 
  // 只有在完全无法将实参转换成std::initializer_list的模板参数时，才会检查普通的重载
  // 例如容器类型为std::string时
  Widget w8{10, 10, 5.0};
  
  // 讨论1：一个空的大括号代表默认构造 还是 空的std::initializer_list
  // 答案：默认构造

  Widget w9{}; 
  // 如果确实希望意为空的std::initializer_list可以将空的std::initializer_list作为显式实参
  Widget w10({}); 
  // 或
  Widget w11{{}}; 

  // 讨论2：带来的影响
  // 例如std::vector有个形参中不带std::initializer_list的构造函数，同时也有带std::initializer_list的构造函数
  // 此时如果只给std::vector的构造函数传递两个参数，则使用的方式与结果有很大不同

  std::vector<int> v1(10, 20);  // 创建了包含10个元素为20的std::vector
  std::vector<int> v2{10, 20};  // 创建了包含两个元素为10、20的std::vector

  // 最好把构造函数设计为无论使用大括号还是小括号都不影响其调用的重载版本
  // 换言之，一般认为std::vector的这种构造接口设计是败笔，要汲取教训

  // 经验教训1：在没有形参为std::initializer_list的构造函数的类中
  // 添加一个std::initializer_list版本的构造函数可能会导致之前使用大括号构造的对象转而调用该版本构造函数

  // 经验教训2：在构造对象时对选择大括号还是小括号要三思而后行
  

  return 0; 
}

// 模板开发中，大括号与小括号的选择也是头疼的问题
// 假设要在下方模板中以任意实参构造一个对象

template<typename T, typename... Ts> 
void doSomething(Ts&& ...paras) {
  T localObj1(std::forward<Ts>(paras)...); // 采用小括号构造对象
  T localObj2{std::forward<Ts>(paras)...}; // 采用大括号构造对象

  std::cout << localObj1.size() << std::endl; 
  std::cout << localObj2.size() << std::endl; 
}

// 考虑调用代码
// doSomething<std::vector<int>>(10, 20); 
// 则大括号与小括号构造出来的对象不一样