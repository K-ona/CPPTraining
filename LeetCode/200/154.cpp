class Solution {
 public:
  int findMin(vector<int>& nums) {
    int l = 0, r = nums.size() - 1;
    while (l < r) {
      if (nums[l] < nums[r])
        return nums[l];
      
      int mid = (l + r) >> 1; 
      if (nums[l] == nums[mid] && nums[mid]== nums[r]) {
        ++l, --r; 
        continue;
      } 

      if (nums[mid] <= nums[r])
        r = mid - 1; 
      else 
        l = mid + 1; 

    }
    return nums[l];
  }
};