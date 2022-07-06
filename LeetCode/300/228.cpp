class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> res;
        res.reserve(nums.size()); 
        int pos = 0; 
        for (int i = 1; i <= nums.size(); ++i) {
            if (i == nums.size() || nums[pos] - pos + i != nums[i]) {
                res.emplace_back(nums[pos] != nums[i - 1] ? (std::to_string(nums[pos]) + "->" + std::to_string(nums[i - 1])) : 
                                                            (std::to_string(nums[pos])));
                pos = i; 
                if (i != nums.size())
                    --i; 
            }
        }
        return res; 
    }
};