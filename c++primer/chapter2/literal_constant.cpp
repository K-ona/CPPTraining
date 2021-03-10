#include <bits/stdc++.h>

using namespace std;

int main()
{
    int x = 077; 
    double y = 1e3L; 
    wchar_t s[] = L"12345"; 
    cout << sizeof(s[0]) << endl; 
    cout << "123\b45%" << endl; 
    cout << "\x2d" << endl; 
    cout << s << endl; 
    cout << y << endl; 
    cout << x << endl; 
    char t[] = "123" "789"
             "456"; 
    // char t[] = "123" L"789"
    //          "456"; 
    // 执行失败
    cout << t << endl;  
    
    // 3.14e1L, "\145\012 ?", 1024f, 3.14UL;
    // 1024f: 整型字面常量不能转为浮点型
    // 3.14UL 浮点字面常量不能转为unsigned
    return 0; 
}