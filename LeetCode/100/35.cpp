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
  int searchInsert(vector<int>& nums, int target) {
    int l = 0, r = static_cast<int>(nums.size()); 
    while (l < r) {
      int mid = (l + r) >> 1; 
      if (nums[mid] < target) {
        l = mid + 1; 
      } else {
        r = mid; 
      }
    }
    return l; 
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