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
  bool search(vector<int>& nums, int target) {
    if (target == nums[0] or target == nums.back()) return true; 
    int l = 0, r = nums.size() - 1;
    while (l < r) {
      int mid = (l + r) >> 1;
      if (nums[mid] == target) return true; 
      if (nums[mid] == nums[l] and nums[mid] == nums[r]) l++, r--;
      else if (nums[mid] >= nums[l]) {
        if (target >= nums[l] and target < nums[mid]) {
          r = mid - 1;
        } else {
          l = mid + 1;
        }
      } else {
        if (target > nums[mid] and target <= nums[r]) {
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
    }
    return nums[l] == target; 
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