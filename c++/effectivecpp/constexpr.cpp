// created by Kona @VSCode
#include <iostream>
#include <array>
#include <string.h>

typedef long long ll;
using std::cin;
using std::cout;
using std::string;

int n = 9; 
constexpr int pow(int x, int y) noexcept {
  int res = 1; 
  for (int i = 0; i < y; ++i) {
    res *= x;
  }
  // std::cout << res << std::endl; // 不允许调用非constexpr函数

  return res; 
}

int main() {

  constexpr int x = pow(2, 9); 
  std::array<int, x> arr;

  return 0;
}