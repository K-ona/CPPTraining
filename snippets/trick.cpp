/*********************** 1. 获取结构体内成员偏移量 **********/

#if 1

#pragma pack(4)
#include <iostream>

// 宏定义offsetof
// #define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)
// gnu编译器已有定义：
// #define offsetof(TYPE, MEMBER) __builtin_offsetof (TYPE, MEMBER)
// 使用alignof查询类型的对齐参数
// c++ <type_traits>中std::alignment_of有类似功能

using std::cout; 
using std::endl;  

struct P {
    char c; 
    double x, y, z; 
    int id; 
};

struct test2 {
    int i;//4byte
    char c = '1';//1byte 
    char d = '2'; //1byte
    short s = 2;//2byte
};

int main()
{
    cout << "alignment of test2 == " << alignof(test2) << endl; 
    cout << "sizeof test2 == " << sizeof(test2) << endl; 
    cout << "offset of i == " << (int)&((test2 *)nullptr)->i << endl; 
    cout << "offset of c == " << (int)&((test2 *)nullptr)->c << endl; 
    cout << "offset of d == " << (int)&((test2 *)nullptr)->d << endl; 
    cout << "offset of x == " << (int)&((test2 *)nullptr)->s << endl; 
    // 等价于
    // cout << "offset of i == " << offsetof(test2, i) << endl; 
    // cout << "offset of c == " << offsetof(test2, c) << endl; 
    // cout << "offset of d == " << offsetof(test2, d) << endl; 
    // cout << "offset of x == " << offsetof(test2, s) << endl; 
    cout << "\n****************************************************\n" << endl; 

    cout << "alignment of P == " << alignof(P) << endl; 
    cout << "sizeof P == " << sizeof(P) << endl; 
    cout << "offset of c == " << (int)&((P *)nullptr)->c << endl; 
    cout << "offset of x == " << (int)&((P *)nullptr)->x << endl; 
    cout << "offset of y == " << (int)&((P *)nullptr)->y << endl; 
    cout << "offset of z == " << (int)&((P *)nullptr)->z << endl; 
    cout << "offset of id == " << (int)&((P *)nullptr)->id << endl; 

    return 0;
}
#endif

/********************************/

/*********************** 2.实现基于范围的反向for循环 **********/

#if 0

#include <iostream>
#include <vector>
#include <list>

// -------------------------------------------------------------------
// --- Reversed iterable
 
template <typename T>
struct reversion_wrapper { T& iterable; };
 
template <typename T>
auto begin (reversion_wrapper<T> w) { return std::rbegin(w.iterable); }
 
template <typename T>
auto end (reversion_wrapper<T> w) { return std::rend(w.iterable); }
 
template <typename T>
reversion_wrapper<T> reverse (T&& iterable) { return { iterable }; }

template <typename T>
void print_iterable (std::ostream& out, const T& iterable)
{
    for (auto&& element: iterable)
        out << element << ',';
    out << '\n';
}

int main (int, char**)
{
 
    // on prvalues
    print_iterable(std::cout, ::reverse(std::initializer_list<int> { 1, 2, 3, 4, }));
 
    // on const lvalue references
    const std::list<int> ints_list { 1, 2, 3, 4, };
    for (auto&& el: reverse(ints_list))
        std::cout << el << ',';
    std::cout << '\n';
 
    // on mutable lvalue references
    std::vector<int> ints_vec { 1, 2, 3, 4, };
    print_iterable(std::cout, ints_vec);
    print_iterable(std::cout, ::reverse(ints_vec));

    return 0;
}
#endif

/********************************/

/*********************** 3.宏处理指令 **********/

#if 0
// 对齐单元
#pragma pack(4)

#include <iostream>

using std::cout; 
using std::endl;  

#define Conn(x,y) x##y

#define ToString(x) #x

int main()
{
    auto x = Conn(1, 2); 
    auto y = ToString(2); 
    return 0;
}
#endif

/********************************/