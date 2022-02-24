// 代码来自 https://blog.csdn.net/sinat_21107433/article/details/108552472
#include <iostream>

using std::cout;
using std::endl;

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
  printf("vptr: 0x%x\n", *(int*)pBase);
  // 然后才存放其他成员变量
  printf("%d\n", *(int*)((int*)pBase + 1));
  printf("%d\n", *(int*)((int*)pBase + 2));

  typedef void (*pFunc)();
  pFunc fun;

  for (int i = 0; i < 2; i++) {
    fun = (pFunc) * ((int*)(*(int*)pBase) + i);
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

class A {
 public:
  int a;
};
class B : public A {
 public:
  int b;
};
class C : public A {
 public:
  int c;
};
class D : public B, public C {
 public:
  int d;
};

void Test5() {
  D d;
  // 有歧义
	// d.a = 5;
}

int main() {
  Test1();
  Test2();
  Test3();
  Test4();
  return 0;
}