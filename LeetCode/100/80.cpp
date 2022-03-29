class Solution {
 public:
  int removeDuplicates(vector<int>& nums) {
    int left = 0;
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
      if (i < 2 or nums[i] != nums[left - 2]) {
        nums[left++] = nums[i];
      }
    }
    return left;
  }
};