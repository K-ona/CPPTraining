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
  vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> res; 
    while (res.empty() or nums != res.front()) {
      res.push_back(nums); 
      nextPermutation(nums); 
    }
    return res;
  }

  void nextPermutation(vector<int>& nums) {
    int n = nums.size();
    int anchor = -1;
    for (int i = n - 1; i; --i) {
      if (nums[i] > nums[i - 1]) {
        anchor = i - 1;
        break;
      }
    }
    if (anchor == -1) {
      std::sort(nums.begin() + anchor + 1, nums.end());
      return;
    }

    int mini = anchor + 1;
    for (int i = anchor + 2; i < n; ++i) {
      if (nums[mini] > nums[i] && nums[i] > nums[anchor]) {
        mini = i;
      }
    }
    std::swap(nums[mini], nums[anchor]);
    std::sort(nums.begin() + anchor + 1, nums.end());
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