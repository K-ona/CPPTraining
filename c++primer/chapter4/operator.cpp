//created by Kona @VSCode
#include<bits/stdc++.h>

using namespace std;

int x = 1; 

int func(const char *s) {
    cout << s << endl; 
    return ++x; 
}

int main()
{
    ios_base::sync_with_stdio(false); 

    cout << func("1") + func("2") * func("3") << endl; 
    // g++结果：2 + 3 * 4 == 14
    // 即表达式中函数求值顺序与运算符优先级无关

    cout << func("1") + func("2") * (func("3") + func("4")) << endl; 
    

    return 0;
}