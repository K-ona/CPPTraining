// std::variant since C++17
// std::variant 表示类型安全的联合。

#include <variant>
#include <string>
#include <cassert>
#include <iostream>
 
int main()
{
    std::variant<int, float> v, w;
    // operator=
    v = 42; // v contains int
    // v = 42LL; // v can not contains long long
    
    int i = std::get<int>(v);
    assert(42 == i); // succeeds
    w = std::get<int>(v);
    w = std::get<0>(v); // same effect as the previous line
    w = v; // same effect as the previous line
 
//  std::get<double>(v); // error: no double in [int, float]
//  std::get<3>(v);      // error: valid index values are 0 and 1
 
    try {
      std::get<float>(w); // w contains int, not float: will throw
    }
    catch (const std::bad_variant_access& ex) {
        std::cout << ex.what() << '\n';
    }
 
    using namespace std::literals;
 
    std::variant<std::string> x("abc");
    // converting constructors work when unambiguous
    x = "def"; // converting assignment also works when unambiguous
 
    std::variant<std::string, void const*> y("abc");
    // casts to void const * when passed a char const *
    assert(std::holds_alternative<void const*>(y)); // succeeds
    y = "xyz"s;
    assert(std::holds_alternative<std::string>(y)); // succeeds

    // holds_alternative
    std::variant<int, std::string> vv = "abc";
    std::cout << std::boolalpha
              << "variant holds int? "
              << std::holds_alternative<int>(vv) << '\n'
              << "variant holds string? "
              << std::holds_alternative<std::string>(vv) << '\n';

    // get_if
    auto check_value = [](const std::variant<int, float>& v)
    {
        if(const int* pval = std::get_if<int>(&v))
          std::cout << "variant value: " << *pval << '\n'; 
        else 
          std::cout << "failed to get value!" << '\n'; 
    };
 
    std::variant<int, float> v_3{12}, w_3{3.f};
    check_value(v_3);
    check_value(w_3);


  return 0; 
}