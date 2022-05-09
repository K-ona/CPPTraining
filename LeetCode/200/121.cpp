class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    int in = 10000;
    int ans = 0; 
    for (const auto x: prices) {
        ans = std::max(ans, x - in); 
        if (in > x) in = x; 
    }
    return ans; 
  }
};