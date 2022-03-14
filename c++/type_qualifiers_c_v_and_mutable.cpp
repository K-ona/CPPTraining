#include <iostream>
#include <mutex>

/*******************************************/
// mutable specifier

// 常见于 非引用非 const 类型的非静态类成员的声明中：
class X {
  mutable const int* p;         // OK
  // mutable int* const q;         // ill-formed: error: 'const' 'q' cannot be declared 'mutable'
  // mutable int&       r;         // ill-formed: error: reference 'r' cannot be declared 'mutable'
};


// Mutable 用于指定成员不影响类的外部可见状态
// （通常用于互斥锁、memo caches（备忘录缓存）、惰性求值和访问检测）。
class ThreadsafeCounter {
  mutable std::mutex m; // The "M&M rule": mutable and mutex go together
  int data = 0;
 public:
  int get() const {
    std::lock_guard<std::mutex> lk(m);
    return data;
  }
  void inc() {
    std::lock_guard<std::mutex> lk(m);
    ++data;
  }
};

/*******************************************/
// cv (const and volatile) type qualifiers

// const 对象 - 类型为 const 限定的对象，或 const 对象的非可变子对象。
// 这样的对象不能被修改：直接尝试这样做是编译时错误，尝试间接这样做会导致未定义行为

// volatile 对象 - 类型为 volatile 限定的对象，或 volatile 对象的子对象，或 const-volatile 对象的可变子对象
// 通过 volatile 限定类型的左值表达式进行的每次访问（读取或写入操作、成员函数调用等）都被视为可见的优化副作用，
// 即在单个执行线程中，volatile 访问不能被优化或重新排序，
// 而另一个可见的副作用是 “sequenced-before or sequenced-after the volatile access.”
// 这使得 volatile 对象适合与信号处理程序通信，但不适用于另一个执行线程，参见 std::memory_order)。
// 任何通过非易失性类型的左值引用易失性对象的尝试（例如，通过对非易失性类型的引用或指针）都会导致未定义的行为。

// const volatile 对象 - 类型为 const-volatile 限定的对象、const volatile 对象的非可变子对象、volatile 对象的 const 子对象或 const 对象的非可变 volatile 子对象。
// 既可以作为 const 对象，也可以作为 volatile 对象。


/*******************************************/
// Conversions

// 指向 cv 限定类型的引用和指针可以隐式转换为指向更多 cv 限定类型的引用和指针。特别是，允许​​进行以下转换
// 1. 指向非限定类型的引用/指针可以转换为指向 const 的引用/指针
// 2. 指向非限定类型的引用/指针可以转换为指向 volatile 的引用/指针
// 3. 指向非限定类型的引用/指针可以转换为指向 const volatile 的引用/指针
// 4. 指向 const 类型的引用/指针可以转换为指向 const volatile 的引用/指针
// 5. 指向 volatile 类型的引用/指针可以转换为指向 const volatile 的引用/指针

// 要将指向 cv 限定类型的引用或指针转换为指向较少 cv 限定类型的引用或指针，必须使用 const_cast。


/*******************************************/
// Notes

// 1. 用于声明非局部、非易失性、非模板 (C++14 起)、非内联 (C++17 起) 、未声明为 extern 的变量
//    的 const 限定符为其提供内部链接属性。[C语言中 const 文件范围变量具有外部链接属性。]
// 2. C++ 语法将 mutable 视为存储类说明符，而不是类型限定符，但它不影响存储类型以及链接属性。

// 3. 不推荐使用的关于volatile的用法 (c++20起)
// 		a. volatile 类型的左值作为内置递增/递减运算符的操作数；
// 		b. volatile 类型的左值作为内置直接/复合赋值运算符的左操作数，
//       除非直接赋值表达式出现在 “ unevaluated context ” 或者 “discarded-value expression”；
// 		c. volatile 对象类型作为函数参数类型或返回类型；
//    d. 结构化绑定声明中的 volatile 限定符。

int main()
{
    int n1 = 0;           // non-const object
    const int n2 = 0;     // const object
    int const n3 = 0;     // const object (same as n2)
    volatile int n4 = 0;  // volatile object
    const struct
    {
        int n1;
        mutable int n2;
    } x = {0, 0};      // const object with mutable member
 
    n1 = 1; // ok, modifiable object
//  n2 = 2; // error: non-modifiable object
    n4 = 3; // ok, treated as a side-effect
//  x.n1 = 4; // error: member of a const object is const
    x.n2 = 4; // ok, mutable member of a const object isn't const
 
    const int& r1 = n1; // reference to const bound to non-const object
//  r1 = 2; // error: attempt to modify through reference to const
    const_cast<int&>(r1) = 2; // ok, modifies non-const object n1
 
    const int& r2 = n2; // reference to const bound to const object
//  r2 = 2; // error: attempt to modify through reference to const
//  const_cast<int&>(r2) = 2; // undefined behavior: attempt to modify const object n2
}