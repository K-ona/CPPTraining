#include <vector>

using std::vector; 

class Solution {
    static int n; 
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        n = nums.size(); 
        vector<vector<int>> ans; 
        vector<int> stk; 
        stk.reserve(n); 
        std::sort(nums.begin(), nums.end()); 
        DFS(ans, stk, nums, 0); 
        return ans; 
    }
    void DFS(vector<vector<int>>& ans, vector<int>& stk, vector<int>& nums, int pos) {
        if (pos == n) {
            ans.push_back(stk); 
            return; 
        }
        int j = pos; 
        while (j < n - 1 and nums[j] == nums[j + 1]) {
          stk.push_back(nums[j++]); 
        }
        stk.push_back(nums[j]); 
        while (stk.size() > 0 and stk.back() == nums[j]) {
          DFS(ans, stk, nums, j + 1);
          stk.pop_back(); 
        }
        DFS(ans, stk, nums, j + 1);
    }
};

int Solution::n = 0;