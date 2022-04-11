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

class Solution {
 public:
  int countNumbersWithUniqueDigits(int n) {
    if (n == 0)
      return 1;
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
      ans += get_ans(i);
    }
    return ans;
  }
  int get_ans(int n) {
    if (n == 0)
      return 1;
    if (n == 1)
      return 10;
    int ans = 9;
    for (int i = 1; i < n; ++i) {
      ans *= (10 - i);
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