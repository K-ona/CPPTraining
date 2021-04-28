#include <iostream>
#include <string>
#include <regex>
 
 enum Example: char {
     A, B, C
 }; 


class A {
public:
    static int value; 
}; 

int A::value = 0; 

int fun(const char *s); 

int x = 1; //extern int x = 1;
extern int w; 

void print_z() {
    // std::cout << y << std::endl; error
    static int z = fun("s") + 1; //只执行一次赋值
    z++; 
    std::cout << z << std::endl; 
}

int main()
{
    // std::cout << A << std::endl; 
    // std::cout << A::value << std::endl; 
    int x = 80; 
    // extern int x; 
    std::cout << ::x << std::endl; 
    std::cout << x << std::endl; 

    static int y = x + 2; //不改变作用域与链接属性
    std::cout << y << std::endl; 
    fun("s"); 
    
    // extern int w = 1;
    // 外部变量的局部声明
    // error: 不允许赋值

    std::cout << ::w << std::endl; 

    print_z(); 
    print_z(); 

    return 0; 
}