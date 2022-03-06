// 代码来自 https://blog.csdn.net/sinat_21107433/article/details/108552472
#include <iostream>

using std::cout;
using std::endl;
using ll = long long; 

class Base {
 public:
  Base() {
    cout << "Base::Base()" << endl;
    a = 1;
    b = 2;
  }
  void func_1() { cout << "Base::func_1()" << endl; }
  virtual void func_2() { cout << "Base::func_2()" << endl; }
  virtual void func_3() { cout << "Base::func_3()" << endl; }
  ~Base() { cout << "Base::~Base()" << endl; }

 private:
  int a;
  int b;
};

// ( *(p->vptr)[n] )(p)

/*
 *  Function name: Test1
 *  Description  : 测试类的虚函数表，类中包括两个虚函数
 *                 1. Print size of object base;
 *                 2. Print member of object base;
 *                 3. Get the address of virtual function and call it, which
 * proves the existence of virtual function table. Return       ： None
 */
void Test1() {
  Base base;
  Base* pBase = &base;
  cout << "Base Size: " << sizeof(base) << endl;

  // 虚函数表地址放在对象开始处
  // printf("vptr: 0x%x\n", *(int*)(pBase)); // 32位机器
  cout << "vptr: " << reinterpret_cast<void*>(*reinterpret_cast<ll*>(pBase)) << endl; // 64位机器
  
  // 然后才存放其他成员变量
  // 32位机器
  // printf("%d\n", *(int*)((int*)pBase + 1)); 
  // printf("%d\n", *(int*)((int*)pBase + 2));
  // 64位机器
  printf("Base.a == %d\n", *(int*)((ll*)pBase + 1)); 
  printf("Base.b == %d\n", *((int*)((ll*)pBase + 1) + 1));

  typedef void (*pFunc)();
  pFunc fun;

  // 32位机器
  // for (int i = 0; i < 2; i++) {
  //   fun = (pFunc) * ((int*)(*(int*)pBase) + i);
  //   fun();
  // }
  // 64位机器
  for (int i = 0; i < 2; i++) {
    fun = (pFunc) * ((ll*)(*(ll*)pBase) + i);
    fun();
  }
}

/**********************************************************************/
// 1. 继承但不覆写（overwrite）
class Derived_1 : public Base {
 public:
  Derived_1() {}
  virtual void func_4() { cout << "Derived_1::func_4()" << endl; }
  virtual void func_5() { cout << "Derived_1::func_5()" << endl; }

 private:
  int c = 3;
  int d = 4;
};

/*
 *  Function name: Test2
 *  Description  :
 * 测试继承类的虚函数表，基类中包括两个虚函数，派生类中包含两个虚函数，且不覆写
 *                 1. Print size of object Derived_1;
 *                 2. Print member of object Derived_1;
 *                 3. Get the address of virtual function and call it, which
 * proves the existence of virtual function table. Return       ： None
 */
void Test2() {
  Derived_1 derived_1;
  Derived_1* pDerived_1 = &derived_1;
  cout << "Derived_1 Size : " << sizeof(derived_1) << endl;

  // 虚函数表地址放在对象开始处
  printf("vptr: 0x%x\n", *(int*)(pDerived_1));
  // 然后存放其他成员变量
  printf("%d\n", *(int*)((int*)pDerived_1 + 1));
  printf("%d\n", *(int*)((int*)pDerived_1 + 2));
  printf("%d\n", *(int*)((int*)pDerived_1 + 3));
  printf("%d\n", *(int*)((int*)pDerived_1 + 4));

  // 取出虚函数
  typedef void (*pFunc)();
  pFunc fun;

  /*
   *     Base :: virtual func_2
   *     Base :: virtual func_3
   *     Derived_1:: virtual func_4
   *     Derived_1:: virtual func_5
   */
  for (int i = 0; i < 4; i++) {
    fun = (pFunc) * (((int*)*(int*)pDerived_1) + i);
    fun();
  }
}

/**********************************************************************/
// 2. 继承，子类覆写父类虚函数

class Derived_2 : public Base {
 public:
  Derived_2() {}
  // 覆写func_3
  virtual void func_3() { cout << "Derived_2::func_3()" << endl; };
  virtual void func_6() { cout << "Derived_2::func_6()" << endl; };

 private:
  int e;
  int f;
};

/*
 *  Function name: Test3
 *  Description  :
 * 测试继承类的虚函数表，基类中包括两个虚函数，派生类中包含两个虚函数，覆写基类的其中一个虚函数
 *                 1. Print size of object Derived_2;
 *                 2. Print member of object Derived_2;
 *                 3. Get the address of virtual function and call it, which
 * proves the existence of virtual function table. Return       ： None
 */
void Test3() {
  Derived_2 derived_2;
  Derived_2* pDerived_2 = &derived_2;
  cout << "base3 Size : " << sizeof(Derived_2) << endl;

  // 虚函数表地址放在对象开始处
  printf("vptr: 0x%x\n", *(int*)pDerived_2);
  // 然后存放其他成员变量
  printf("%d\n", *((int*)pDerived_2 + 1));
  printf("%d\n", *((int*)pDerived_2 + 2));
  printf("%d\n", *((int*)pDerived_2 + 3));
  printf("%d\n", *((int*)pDerived_2 + 4));

  typedef void (*pFunc)();
  pFunc fun;

  /*
   *     Base :: virtual func_2
   *     Base3:: virtual func_3
   *     Base3:: virtual func_6
   */
  for (int i = 0; i < 3; i++) {
    fun = (pFunc) * (((int*)*(int*)pDerived_2) + i);
    fun();
  }
}

/**********************************************************************/
// 3. 多重继承下的虚函数表

class Father1 {
 public:
  Father1() { x = 111; }
  virtual void func_1() { cout << "Father1::func_1()" << endl; }

 private:
  int x;
};

class Father2 {
 public:
  Father2() { y = 222; }
  virtual void func_2() { cout << "Father2::func_2()" << endl; }

 private:
  int y;
};

class Child : public Father1, public Father2 {
 public:
  Child() { z = 333; }
  virtual void func_3() { cout << "Child::func_3()" << endl; }

 private:
  int z;
};

/*
 *  Function name: Test4
 *  Description  : 测试继承类的虚函数表，类Child有两个父类Father1和Father2
 *                 1. Print size of object Child;
 *                 2. Print member of object Child;
 *                 3. Get the address of virtual function and call it, which
 * proves the existence of virtual function table. Return       ： None
 */
void Test4() {
  Child child;
  Child* pChild = &child;
  cout << "child Size : " << sizeof(child) << endl;

  // 虚函数表地址放在对象开始处
  printf("vptr 1: 0x%x\n", *(int*)pChild);
  printf("vptr 2: 0x%x\n", *((int*)pChild + 2));
  // 然后存放其他成员变量
  printf("%d\n", *((int*)pChild + 1));
  printf("%d\n", *((int*)pChild + 3));
  printf("%d\n", *((int*)pChild + 4));

  typedef void (*pFunc)();
  pFunc fun;

  /*
   *     Father1 :: virtual func_1
   *     Child:: virtual func_3
   */
  for (int i = 0; i < 2; i++) {
    fun = (pFunc) * (((int*)*(int*)pChild) + i);
    fun();
  }

  /*
   *     Father2 :: virtual func_2
   */
  for (int i = 0; i < 1; i++) {
    fun = (pFunc) * (((int*)*((int*)pChild + 2)) + i);
    fun();
  }
}

/**********************************************************************/
// 4. 虚继承

class Base_virtual
{
    int a = 1;
    int b = 2;
public:
    void CommonFunction();
    void virtual VirtualFunction_1() { cout << "Base_virtual::VirtualFunction_1()" << endl; }
    void virtual VirtualFunction() { cout << "Base_virtual::VirtualFunction()" << endl; }
};

class DerivedClass1: virtual public Base_virtual
{
    int c = 3;
public:
    void DerivedCommonFunction();
    void virtual VirtualFunction_2() { cout << "DerivedClass1::VirtualFunction_2()" << endl; }
    void virtual VirtualFunction() { cout << "DerivedClass1::VirtualFunction()" << endl; }
};

class DerivedClass2 : virtual public Base_virtual
{
    int d = 4;
public:
    void DerivedCommonFunction();
    void virtual VirtualFunction_3() { cout << "DerivedClass2::VirtualFunction_3()" << endl; }
    void virtual VirtualFunction() { cout << "DerivedClass2::VirtualFunction()" << endl; }
};

class DerivedDerivedClass :  public DerivedClass1, public DerivedClass2
{
    int e = 5;
public:
    void DerivedDerivedCommonFunction();
    void virtual VirtualFunction_4() { cout << "DerivedDerivedClass::VirtualFunction_4()" << endl; }
    void virtual VirtualFunction() { cout << "DerivedDerivedClass::VirtualFunction()" << endl; }
};

/*
 *  Function name: Test5
 *  Description  : 测试继承类的虚函数表，类Child有两个父类Father1和Father2
 *                 1. Print size of object Child;
 *                 2. Print member of object Child;
 *                 3. Get the address of virtual function and call it, which
 * proves the existence of virtual function table. Return       ： None
 */
void Test5() {
  cout << "Base_virtual Size : " << sizeof(Base_virtual) << endl;
  cout << "DerivedClass1 Size : " << sizeof(DerivedClass1) << endl;
  cout << "DerivedClass2 Size : " << sizeof(DerivedClass2) << endl;
  cout << "DerivedDerivedClass Size : " << sizeof(DerivedDerivedClass) << endl;

  // 中间类虚表测试
  DerivedClass1 child;
  DerivedClass1* pchild = &child;

  // 有两个虚表指针，一个是虚基类表，一个是自己的虚表
  printf("vptr 1: 0x%x\n", *(int*)pchild);
  printf("vptr 2: 0x%x\n", *((int*)pchild + 2));
  // 然后存放其他成员变量
  printf("%d\n", *((int*)pchild + 1));
  printf("%d\n", *((int*)pchild + 3));
  printf("%d\n", *((int*)pchild + 4));

  typedef void (*pFunc)();
  pFunc fun;

  // 首先是自己的虚函数
  for (int i = 0; i < 1; i++) {
    fun = (pFunc) * (((int*)*(int*)pchild) + i);
    fun();
  }
  // 然后是基类的虚函数
    for (int i = 0; i < 1; i++) {
    fun = (pFunc) * (((int*)*((int*)pchild + 2)) + i);
    fun();
  }

  // 子类虚表测试
  DerivedDerivedClass Child;
  DerivedDerivedClass* pChild = &Child;
  // 有三个虚表指针，一个是虚基类表，加上两个基类虚函数表
  printf("vptr 1: 0x%x\n", *(int*)pChild);
  printf("vptr 2: 0x%x\n", *((int*)pChild + 2));
  printf("vptr 3: 0x%x\n", *((int*)pChild + 5));
  // 然后存放其他成员变量
  printf("%d\n", *((int*)pChild + 1));
  printf("%d\n", *((int*)pChild + 3));
  printf("%d\n", *((int*)pChild + 4));
  printf("%d\n", *((int*)pChild + 6));
  printf("%d\n", *((int*)pChild + 7));

  typedef void (*pFunc)();
  pFunc Fun;

  // 首先是基类1的虚函数(包括被自己改写的函数)
  for (int i = 0; i < 2; i++) {
    Fun = (pFunc) * (((int*)*(int*)pChild) + i);
    Fun();
  }
  // 然后是基类2的虚函数
  for (int i = 0; i < 2; i++) {
    Fun = (pFunc) * (((int*)*((int*)pChild + 2)) + i);
    Fun();
  }
  // 然后是虚基表的虚函数
  for (int i = 0; i < 1; i++) {
    Fun = (pFunc) * (((int*)*((int*)pChild + 5)) + i);
    Fun();
  }
  

}


int main() {
  Test1();
  // Test2();
  // Test3();
  // Test4();
  // Test5();
  return 0;
}