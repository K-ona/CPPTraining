// std::optional (Since C++17)
// https://en.cppreference.com/w/cpp/utility/optional
// 
// optional<T> 可以用来表示一个可能存在的值，或者不存在的值。

// 1. 
// 如果 optional<T> 包含一个值，则保证该值作为 optional<T> 对象占用空间的一部分进行分配，
// 即不会发生动态内存分配。因此，该optional<T> 对象建模了一个对象而不是指针，
// 即使定义了 operator*() 和 operator->()。
// 2. 
// 当 optional<T> 类型的对象根据上下文转换为 bool 时，
// 如果对象包含值，则转换返回 true，如果不包含值，则转换返回 false。
// 3. 
// optional<T> 类型的对象包含一个值当：
// 该对象使用 T 类型的值或另一个包含值的optional<T>进行初始化/赋值。
// 4. 
// optional<T> 类型的对象不包含一个值当：
// 该对象是默认初始化的。
// 该对象由 std::nullopt_t 类型的值或不包含值的optional<T>初始化/赋值。
// optional<T>对象调用成员函数reset()之后。
// 5. 
// 如果一个程序用引用类型实例化一个optional<T>对象，则该程序是格式错误的。
// 可以使用类型T的std::reference_wrapper 来保存引用。

#include <string>
#include <functional>
#include <iostream>
#include <optional>
 
// optional can be used as the return type of a factory that may fail
std::optional<std::string> create(bool b) {
    if (b)
        return "Godzilla";
    return {};
}
 
// std::nullopt can be used to create any (empty) std::optional
auto create2(bool b) {
    return b ? std::optional<std::string>{"Godzilla"} : std::nullopt;
}
 
// std::reference_wrapper may be used to return a reference
auto create_ref(bool b) {
    static std::string value = "Godzilla";
    return b ? std::optional<std::reference_wrapper<std::string>>{value}
             : std::nullopt;
}
 
int main()
{
    std::cout << "create(false) returned "
              << create(false).value_or("empty") << '\n';
    
        std::cout << "create(true) returned "
              << create(true).value_or("empty") << '\n';

    // optional-returning factory functions are usable as conditions of while and if
    if (auto str = create2(true)) {
        std::cout << str.has_value() << "\n"; 
        std::cout << "create2(true) returned " << *str << '\n';
    }
 
    if (auto str = create_ref(true)) {
        // using get() to access the reference_wrapper's value
        std::cout << "create_ref(true) returned " << str->get() << '\n';
        str->get() = "Mothra";
        std::cout << "modifying it changed it to " << str->get() << '\n';
    }
}