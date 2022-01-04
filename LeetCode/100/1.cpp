// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
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
  vector<int> twoSum(vector<int>& nums, int target) {
    auto tmp = nums;
    std::sort(nums.begin(), nums.end());
    int s = -1, t = -1;
    for (int i = 0; i < nums.size(); ++i) {
      auto p =
          std::lower_bound(nums.begin() + i + 1, nums.end(), target - nums[i]);
      if (p != nums.end() && *p == target - nums[i]) {
        s = nums[i];
        t = target - nums[i];
        break;
      }
    }
    vector<int> res{-1, -1};
    for (int i = 0; i < tmp.size(); ++i) {
      if (tmp[i] == s && res[0] == -1) {
        res[0] = i;
      } else if (tmp[i] == t && res[1] == -1) {
        res[1] = i;
      }
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