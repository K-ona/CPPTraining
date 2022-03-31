// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
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

inline long double C_n_m(int n, int m) {
  if (n < m) {
    return 0;
  }
  long double res = 1;
  for (int i = 1; i <= m; ++i) {
    res *= n - i + 1;
    res /= i;
  }
  return res;
}

class Solution {
 public:
  int uniquePaths(int m, int n) { return C_n_m(m + n - 2, m - 1); }
};

class Solution {
 public:
  int uniquePaths(int m, int n) {
    long long ans = 1;
    for (int x = n, y = 1; y < m; ++x, ++y) {
      ans = ans * x / y;
    }
    return ans;
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