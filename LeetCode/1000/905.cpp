class Solution {
 public:
  vector<int> sortArrayByParity(vector<int>& nums) {
    int end = nums.size();
    for (int i = 0; i < end; ++i) {
      if (nums[i] & 1) {
        std::swap(nums[i], nums[--end]);
        --i;
      }
    }
    return nums;
  }
};