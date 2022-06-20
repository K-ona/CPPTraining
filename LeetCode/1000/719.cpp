class Solution {
  int k;

 public:
  bool check(int sum, vector<int>& nums) {
    int n = nums.size();
    int check = 0;
    for (int i = 0; i + 1 < n; ++i) {
      check +=
          std::upper_bound(nums.begin() + i + 1, nums.end(), sum + nums[i]) -
          nums.begin() - i - 1;
    }
    return check >= k;
  }

  int smallestDistancePair(vector<int>& nums, int k) {
    int n = nums.size();
    this->k = k;
    std::sort(nums.begin(), nums.end());
    int l = 0, r = nums.back() - nums.front();
    while (l < r) {
      int mid = (l + r) >> 1;
      // cout << l << " " << r << endl;
      if (check(mid, nums)) {
        r = mid;
      } else
        l = mid + 1;
    }
    return l;
  }
};