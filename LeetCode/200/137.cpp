class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0; 
        int len = nums.size();
        for (int i = 0; i < 32; ++i) {
           int cnt = 0; 
           for (const auto &num: nums) {
               num & (1 << i) ? ++cnt : 0; 
           }
           res |= (cnt % 3) << i; 
        }
        return res; 
    }
};
