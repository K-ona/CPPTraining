/*********************** 1. 获取结构体内成员偏移量 **********/

#if 0

#pragma pack(4)
#include <iostream>

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
    short s = 2;//2byte
};

int main()
{
    cout << "sizeof test2 == " << sizeof(test2) << endl; 
    cout << "offset of i == " << (int)&((test2 *)nullptr)->i << endl; 
    cout << "offset of c == " << (int)&((test2 *)nullptr)->c << endl; 
    cout << "offset of x == " << (int)&((test2 *)nullptr)->s << endl; 

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

#if 1

#include <iostream>
#include <vector>

int main()
{

    std::vector<int> arr{1, 2, 3, 4, 5}; 

    return 0;
}
#endif

/********************************/

/*********************** 3.宏处理指令 **********/

#if 0
#pragma pack(4)

#include <iostream>

using std::cout; 
using std::endl;  

#define Conn(x,y) x##y

#define ToString(x) #x

int main()
{

    return 0;
}
#endif

/********************************/