/*********************** 获取结构体内成员偏移量 **********/
#include <iostream>

using std::cout; 
using std::endl;  

struct P {
    char c; 
    double x, y, z; 
    int id; 
};

int main()
{
    int offs = (int)&((P *)nullptr)->id; 
    cout << offs << endl; 

    return 0;
}

/********************************/