//created by Kona @VSCode
#include<bits/stdc++.h>

using namespace std;

int x = 1; 

int func(const char *s) {
    cout << s << endl; 
    return ++x; 
}

struct entity
{
    int x; 
    enum {
        A, B, C
    };

    int get() {
        return 1; 
    }
    
    int &getx() {
        return this->x; 
    }

};


int main()
{
    ios_base::sync_with_stdio(false); 

    cout << func("1") + func("2") * func("3") << endl; 
    // g++结果：2 + 3 * 4 == 14
    // 即表达式中函数求值顺序与运算符优先级无关

    cout << func("1") + func("2") * (func("3") + func("4")) << endl; 
    
    // 算数运算
    cout << ( 1 + -2 ) << endl; 

    // ++ / --
    int a = 5; 
    cout << (++a += 1) << endl; 
    cout << a << endl; // pre ++ 返回左值
    // 后置++返回右值

    int &&ref = 5; 
    cout << ref << endl; 
    ref += 1; 
    cout << ref << endl; 
    

    return 0;
