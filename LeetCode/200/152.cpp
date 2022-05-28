int f[20005][2];

class Solution {
 public:
  int maxProduct(vector<int>& nums) {
    int n = nums.size();
    f[0][0] = std::max(0, nums[0]);
    f[0][1] = std::min(0, nums[0]);

    int ans = nums[0];
    for (int i = 1; i < n; ++i) {
      f[i][0] =
          std::max({f[i - 1][1] * nums[i], f[i - 1][0] * nums[i], nums[i]});
      f[i][1] =
          std::min({f[i - 1][1] * nums[i], f[i - 1][0] * nums[i], nums[i]});
      ans = std::max(ans, f[i][0]);
    }
    return ans;
  }
};