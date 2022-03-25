//created by Kona @VSCode
#include <iostream>
#include <vector>


// #define STATIC
#ifdef STATIC
// static_cast
// 不能丢失 const 和 volatile 属性
struct B
{
    int m = 42;
    const char* hello() const
    {
        return "Hello world, this is B!\n";
    }
};
 
struct D : B
{
    const char* hello() const
    {
        return "Hello world, this is D!\n";
    }
};
 
enum class E { ONE = 1, TWO, THREE };
enum EU { ONE = 1, TWO, THREE };
 
int main()
{
    // 1. static downcast for reference or pointer
    D d;
    B& br = d; // upcast via implicit conversion
    std::cout << "1) " << br.hello();
    D& another_d = static_cast<D&>(br); // downcast
    std::cout << "1) " << another_d.hello();
 
    // 2. lvalue to xvalue
    std::vector<int> v0{1,2,3};
    std::vector<int> v2 = static_cast<std::vector<int>&&>(v0); // 右值触发移动复制
    std::cout << "2) after move, v0.size() = " << v0.size() << '\n';
 
    // 3. initializing conversion
    int n = static_cast<int>(3.14);
    std::cout << "3) n = " << n << '\n';
    std::vector<int> v = static_cast<std::vector<int>>(10);
    std::cout << "3) v.size() = " << v.size() << '\n';
 
    // 4. discarded-value expression
    static_cast<void>(v2.size());
 
    // 5. inverse of implicit conversion
    void* nv = &n;
    int* ni = static_cast<int*>(nv);
    std::cout << "5) *ni = " << *ni << '\n';
 
    // 6. array-to-pointer followed by upcast
    // 如果表达式到新类型的转换涉及左值到右值、数组到指针或函数到指针的转换，
    // 则可以通过 static_cast 显式执行
    D a[10];
    [[maybe_unused]]
    B* dp = static_cast<B*>(a);

    // 7. scoped enum to int
    // 结果与从枚举的基础类型到目标类型的隐式转换相同
    E e = E::TWO;
    int two = static_cast<int>(e);
    std::cout << "7) " << two << '\n';
 
    // 8. int to enum, enum to another enum
    E e2 = static_cast<E>(two);
    [[maybe_unused]]
    EU eu = static_cast<EU>(e2);
 
    // 9. pointer to member upcast
    int D::*pm = &D::m;
    std::cout << "9) " << br.*static_cast<int B::*>(pm) << '\n';
 
    // 10. void* to any type
    void* voidp = &e;
    [[maybe_unused]]
    std::vector<int>* p = static_cast<std::vector<int>*>(voidp);
}

// 总结：static_cast < new-type > ( expression ) 的结果类型	
// 1. 如果 new-type 是左值引用类型或对函数类型的右值引用，则为 lvalue
// 2. 如果 new-type 是对对象类型的右值引用，则为 xvalue
// 3. 否则为prvalue。

#endif

#define CONST
#ifdef CONST

// const_cast: const_cast < new-type > ( expression )		
// 只有 const_cast 可以用来抛弃 常量性(constness ) 和 挥发性(volatility)
// 可以执行下列操作
// 1. 两个可能指向同一类型的多级指针可以在彼此之间转换，而不管每个级别的 cv 限定符。
// 2. 任何类型 T 的左值都可以转换为对相同类型 T 的左值或右值引用，或多或少是 cv 限定的。
//    同样，class 类型的纯右值或任何类型的 xvalue 都可以转换为 或多或少有 cv 限定的右值引用。
//    如果 expression 是 glvalue，则 const_cast 的结果是指原始对象，否则是物化的临时对象（C++17 起）。
// 3. 

#include <iostream>
 
struct type
{
    int i;
 
    type(): i(3) {}
 
    void f(int v) const
    {
        // this->i = v;                 // compile error: this is a pointer to const
        const_cast<type*>(this)->i = v; // OK as long as the type object isn't const
    }
};
 
int main() 
{
    int i = 3;                 // i is not declared const
    const int& rci = i; 
    const_cast<int&>(rci) = 4; // OK: modifies i
    std::cout << "i = " << i << '\n';
 
    type t; // if this was const type t, then t.f(4) would be undefined behavior
    t.f(4);
    std::cout << "type::i = " << t.i << '\n';
 
    const int j = 3; // j is declared const
    [[maybe_unused]]
    int* pj = const_cast<int*>(&j);
    // *pj = 4;      // undefined behavior
 
    [[maybe_unused]]
    void (type::* pmf)(int) const = &type::f; // pointer to member function
    // const_cast<void(type::*)(int)>(pmf);   // compile error: const_cast does
                                              // not work on function pointers
}

// 总结：const_cast < new-type > ( expression ) 的结果类型


#endif
