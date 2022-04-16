// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>

#include <string.h>
#include <math.h>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::queue;
using std::string;
using std::vector;

class Solution {
 public:
  int largestPalindrome(int n) {
    if (n == 1) {
      return 9;
    }
    int upper = ::pow(10, n) - 1;
    for (int left = upper;; --left) {  // 枚举回文数的左半部分
      long p = left;
      for (int x = left; x > 0; x /= 10) {
        p = p * 10 + x % 10;  // 翻转左半部分到其自身末尾，构造回文数 p
      }
      for (long x = upper; x * x >= p; --x) {
        if (p % x == 0) {  // x 是 p 的因子
          return p % 1337;
        }
      }
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  return 0;
}