// (c++20起) 
// consteval - 指定一个函数是一个立即函数，也就是说，对函数的每次调用都必须产生一个编译时常量


consteval int sqr(int n) {
  return n*n;
}
constexpr int r = sqr(100); // OK
 
int x = 100;
int r2 = sqr(x);            // Error: Call does not produce a constant
                            // x 不是常量
 
consteval int sqrsqr(int n) {
  return sqr(sqr(n));       // Not a constant expression at this point, but OK
}
 
constexpr int dblsqr(int n) {
  return 2*sqr(n);          // Error: Enclosing function is not consteval
                            // and sqr(n) is not a constant
                            // n 不是常量
}






#include <iostream>
 
// This function might be evaluated at compile-time, if the input
// is known at compile-time. Otherwise, it is executed at run-time.
constexpr unsigned factorial(unsigned n) {
    return n < 2 ? 1 : n * factorial(n - 1);
}
 
// With consteval we have a guarantee that the function will be evaluated at compile-time.
consteval unsigned combination(unsigned m, unsigned n) {
    return factorial(n) / factorial(m) / factorial(n - m);
}
 
static_assert(factorial(6) == 720);
static_assert(combination(4,8) == 70);
 
int main(int argc, const char*[]) {
 
    constexpr unsigned x{factorial(4)};
    std::cout << x << '\n';
 
    [[maybe_unused]]
    unsigned y = factorial(argc); // OK
//  unsigned z = combination(argc, 7); // error: 'argc' is not a constant expression
}