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
 public:
  int largestSumAfterKNegations(vector<int>& nums, int k) {
    std::sort(nums.begin(), nums.end());
    int sum = 0;
    for (auto const& x : nums) {
      if (x < 0 && k) {
        sum -= x;
        --k;
      } else {
        sum += x;
      }
    }
    if (k % 2) {
      auto p = std::lower_bound(nums.begin(), nums.end(), 0);
      long long num = *p;
      sum += (num == 0)
                 ? 0
                 : (p == nums.begin()
                        ? -2 * num
                        : (p == nums.end() ? 2 * *--p
                                           : 2 * std::max(-num, 1LL * *--p)));
    }
    return sum;
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