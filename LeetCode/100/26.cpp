class Solution {
 public:
  int removeDuplicates(vector<int>& nums) {
    int left = 0;
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
      if (!i or nums[i] != nums[i - 1]) {
        nums[left++] = nums[i];
      }
    }
    return left;
  }
};