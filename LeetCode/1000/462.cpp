class Solution {
public:
    int minMoves2(vector<int>& nums) {
        std::sort(nums.begin(), nums.end()); 
        int n = nums.size(); 
        int ans = 0; 
        int mean = nums[n / 2]; 
        for (int i = 0; i < n / 2; ++i) {
            ans += nums[n - 1 - i] - nums[i]; 
        }
        return ans; 
    }
};