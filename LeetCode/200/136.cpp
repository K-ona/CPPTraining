int len;
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        ::len = nums.size();
        for (int i = 1; i < len; ++i) {
            nums[i] ^= nums[i - 1];
        }
        return nums[len - 1];  
    }
};