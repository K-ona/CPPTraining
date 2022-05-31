#include <vector>

class Solution {
 public:
  // 置换法：将元素换到正确的位置
  int firstMissingPositive_1(std::vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
      while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
        std::swap(nums[nums[i] - 1], nums[i]);
      }
    }
    for (int i = 0; i < n; ++i) {
      if (nums[i] != i + 1) {
        return i + 1;
      }
    }
    return n + 1;
  }

  // 原地hash法：用负数表示当前值出现过，不改变数值，因此不会漏
  int firstMissingPositive_2(std::vector<int>& nums) {
    int n = nums.size();
    for (int& num : nums) {
      if (num <= 0) {
        num = n + 1;
      }
    }
    for (int i = 0; i < n; ++i) {
      int num = abs(nums[i]);
      if (num <= n) {
        nums[num - 1] = -abs(nums[num - 1]);
      }
    }
    for (int i = 0; i < n; ++i) {
      if (nums[i] > 0) {
        return i + 1;
      }
    }
    return n + 1;
  }
};