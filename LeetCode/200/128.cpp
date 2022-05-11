class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        std::unordered_set<int> dp; 
        for (const auto &x: nums) {
            dp.insert(x); 
        }

        int res; 
        for (auto x: dp) {
          int cnt = 1; 
          if (dp.count(x - 1)) continue; 
          while(dp.count(x + 1)) {
            ++x; 
            ++cnt; 
          }
          if (cnt > res) res = cnt;
        }
        return res; 
    }
};