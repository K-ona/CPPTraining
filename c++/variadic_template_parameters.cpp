#include <iostream>

// variadic_template_parameters class
template<typename... Args>
struct Sum {};

template <typename First, typename... Rest>
struct Sum<First, Rest...> {
  enum { value = Sum<First>::value + Sum<Rest...>::value };
};

template <typename Last>
struct Sum<Last> {
  enum { value = sizeof(Last) };
};

template <>
struct Sum<> { enum{ value = 0 }; };


// variadic_template_parameters expand by inherited
// 整型序列的定义
template<int...>
struct IndexSeq{};

// 继承方式，开始展开参数包
template<int N, int... Indexes>
struct MakeIndexes : MakeIndexes<N - 1, N - 1, Indexes...> {};

// 模板特化，终止展开参数包的条件
template<int... Indexes>
struct MakeIndexes<0, Indexes...>
{
    typedef IndexSeq<Indexes...> type;
};


void tprintf(const char* format)  // base function
{
  std::cout << format;
}

template <typename T, typename... Targs>
void tprintf(const char* format,
             T value,
             Targs... Fargs)  // recursive variadic function
{
  for (; *format != '\0'; format++) {
    if (*format == '%') {
      std::cout << value;
      tprintf(format + 1, Fargs...);  // recursive call
      return;
    }
    std::cout << *format;
  }
}

int main() {
  tprintf("% world% %\n", "Hello", '!', 123);
  std::cout << Sum<>::value << std::endl;
  return 0; 
}