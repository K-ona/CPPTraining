// std::any since C++17
// any 类为任何可复制构造类型的 单个值 描述了一个类型安全的容器。

// 1. 
// any 类的对象存储 满足构造函数要求或为空 的任何类型的实例
// 这被称为any 类的状态。存储的实例称为被包含对象。
// 2. 
// 非成员 any_cast 函数提供对包含对象的类型安全访问。
#include <any>
#include <iostream>
 
int main()
{
    std::cout << std::boolalpha;
 
    // any type
    std::any a = 1;
    std::cout << a.type().name() << ": " << std::any_cast<int>(a) << '\n';
    a = 3.14;
    std::cout << a.type().name() << ": " << std::any_cast<double>(a) << '\n';
    a = true;
    std::cout << a.type().name() << ": " << std::any_cast<bool>(a) << '\n';
 
    // bad cast
    try
    {
        a = 1;
        std::cout << std::any_cast<float>(a) << '\n';
    }
    catch (const std::bad_any_cast& e)
    {
        std::cout << e.what() << '\n';
    }
 
    // has value
    a = 2;
    if (a.has_value())
    {
      std::cout << a.type().name() << ": " << std::any_cast<int>(a) << '\n';
    }
 
    // reset
    a.reset();
    if (!a.has_value())
    {
        std::cout << "no value\n";
    }
 
    // pointer to contained data
    a = 3;
    int* i = std::any_cast<int>(&a);
    std::cout << *i << "\n";
}