class Solution {
 public:
  int smallestRangeI(vector<int>& nums, int k) {
    int Max = 0;
    int Min = 10000;
    for (auto x : nums) {
      Max = max(Max, x);
      Min = min(Min, x);
    }
    if (Max - Min <= 2 * k)
      return 0;
    else {
      return abs(Max - Min - 2 * k);
    }
  }
};