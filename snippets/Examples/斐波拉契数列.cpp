// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

#include <string.h>

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
  const int mod = 1000000007; 
 public:
  int fib(int n) {
    int a = 0;
    int b = 1;
    if (!n)
      return 0;
    while (--n) {
      b = (a + b) % mod;
      a = ((b - a) % mod + mod) % mod;
    }
    return b;
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