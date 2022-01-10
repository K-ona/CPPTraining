// created by Kona @VSCode
// rule 1: 理解模板型别推导

// 函数模板示例如下：
// template <typename T>
// void func(Paramtype param);

// 对函数模板的形参的型别paramtype以及模板参数T的型别进行推导
// 分为三种情况

#include <iostream>

using std::cout;
using std::endl;

int get_tmp() {
  return rand();
}
// 情景1：Paramtype是指针或引用但不是万能引用
template <typename T>
void func1(T* param) {
  cout << "situation 1.1" << endl;
}

template <typename T>
void func1_const(T* const param) {
  cout << "situation 1.2" << endl;
}

template <typename T>
void func1(T& param) {
  cout << "situation 1.3" << endl;
}

template <typename T>
void func1(const T& param) {
  cout << "situation 1.4" << endl;
}

// 情景2：Paramtype是万能引用
template <typename T>
void func2(T&& param) {
  cout << param << endl; 
}

// 情景3：Paramtype既非引用也非指针
template <typename T>
void func3(T param) {
  cout << param << endl; 
}

int main() {
  const char* s = "string";
  int x = 27;
  const int cx = x;
  const int& rx = x;

/****************************************************************************************/
// 情景1：Paramtype是指针或引用但不是万能引用，此时T和Paramtype的推导结果如下：

  // void func<int>(int &param)
  func1(x);

  // void func<const int>(const int &param)
  // 向型别 T& 传入const对象，T可以接收参数的const属性
  func1(cx);

  // void func<const int>(const int &param)
  // 注意：即使实参是引用类型，T也没有被推导成引用类型，实参的引用性会被忽略
  func1(rx);

  // void func1<int>(const int &param)
  func1(x);

  // void func1<int>(const int &param)
  // 没有意外，若Paramtype含有const，则T不接收const属性  
  func1(cx);

  // void func1<int>(const int &param)
  // 实参的引用性仍会被忽略
  func1(rx);

  // void func<const char>(const char *param)
  func1(s);

  const char* const test = "test";
  // void func1<const char>(const char *param)
  // 由此可见此时T接收了底层const属性
  func1(test);

  // 用该模板函数形式维护指针顶层const属性
  func1_const(test);
/****************************************************************************************/

/****************************************************************************************/
// 情景2：Paramtype是万能引用，当parameter是左值时，
// 这是T被推导成为引用类型的唯一情况
// 具体示例如下：
  
  // 右值，T的表现情况与情况1相同
  // void func2<int>(int &&param)
  func2(1); 

  int&& crx = get_tmp(); 
  crx = 2; 

  // 若为左值，则T推导为引用类型
  // void func2<int &>(int &param)
  func2(crx); 

  // void func2<int &>(int &param)
  func2(x); 

  // void func2<const int &>(const int &param)
  func2(cx); 

  // void func2<const int &>(const int &param)
  func2(rx); 
/****************************************************************************************/

/****************************************************************************************/
// 情景3：Paramtype既非指针也非引用
// 按值传递参数，param是实参的副本，忽略实参 的引用性、顶层const、volatile

// void func3<int>(int param)
  func3(x); 

// void func3<int>(int param)
  func3(cx); 

// void func3<int>(int param)
  func3(rx); 

  const char* const ptr = "test"; 
// void func3<const char *>(const char *param)
// 由于按值传递，顶层const被忽略，底层const仍保留
  func3(ptr); 

  return 0;
}