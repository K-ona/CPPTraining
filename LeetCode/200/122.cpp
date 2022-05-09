int dp[30005][2];
class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    dp[0][0] = 0;
    dp[0][1] = -prices[0];
    int n = prices.size();
    for (int i = 1; i < n; ++i) {
      dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
      dp[i][1] = std::max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
    }
    return dp[n - 1][0];
  }
};