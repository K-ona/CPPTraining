class Solution {
 public:
  int minSubArrayLen(int target, vector<int>& nums) {
    int min = 1000000;
    int l = 0, r = 0;
    int sum = 0;
    while (l < nums.size()) {
      while (sum < target && r < nums.size()) {
        sum += nums[r++];
      }
      if (sum >= target)
        min = std::min(min, r - l);
      sum -= nums[l++];
    }
    return min == 1000000 ? 0 : min;
  }
};