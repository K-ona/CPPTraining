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
  /**
   * @param nums: the given array
   * @return: any element appear two and more times
   */
  int findRepeatNumber(vector<int>& nums) {
    for (int i = 0; i < nums.size(); i++) {
      // cout << "i == " << i << " num[i] == " << nums[i] << endl;
      if (nums[i] != i) {
        if (nums[nums[i]] == nums[i]) {
          return nums[i];
        } else {
          std::swap(nums[nums[i]], nums[i]);
        }
      }
    }
    return 0;
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