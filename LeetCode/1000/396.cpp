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
  int maxRotateFunction(vector<int>& nums) {
    int f = 0, n = nums.size();
    int numSum = std::accumulate(nums.begin(), nums.end(), 0);
    for (int i = 0; i < n; i++) {
      f += i * nums[i];
    }
    int res = f;
    for (int i = n - 1; i > 0; i--) {
      f += numSum - n * nums[i];
      res = std::max(res, f);
    }
    return res;
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