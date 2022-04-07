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
  void sortColors(vector<int>& nums) {
    int l = 0, r = nums.size() - 1;
    int left = 0, right = nums.size() - 1;
    while (left < right and l < r) {
      if (nums[l] == 0) {
        ++l; 
        continue;
      }
      if (nums[r] == 2) {
        --r;
        continue;
      }
      if (nums[l] == 2 and nums[r] == 0) {
        std::swap(nums[l++], nums[r--]);
        continue; 
      } 
      if (nums[l] == 2) {
        std::swap(nums[l], nums[r--]);
        continue;
      }
      if (nums[r] == 0) {
        std::swap(nums[l++], nums[r]);
        continue;
      }
      if (left < l) left = l; 
      if (right > r) right = r;
      while (left < right && nums[left] == 1) ++left;
      if (left == right) break;
      std::swap(nums[left], nums[l]);
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
      