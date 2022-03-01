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
  int threeSumClosest(vector<int>&& nums, int target) {
    int n = nums.size(); 
    int res = 100000; 
    std::sort(nums.begin(), nums.end()); 
    for (int i = 0; i < n; ++i) { 
      int k = n - 1; 
      for (int j = i + 1; j < k; ) {
        int tmp = nums[i] + nums[j] + nums[k]; 
        if (std::abs(tmp - target) < std::abs(res - target)) {
          res = tmp; 
        }
        tmp > target ? --k : ++j;
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

  Solution().threeSumClosest({0, 2, 1, -3}, 1); 
  return 0;
}