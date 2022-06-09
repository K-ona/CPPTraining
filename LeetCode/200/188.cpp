int dp[1005][105][2];
class Solution {
 public:
  int maxProfit(int k, vector<int>& prices) {
    int n = prices.size();
    if (n == 0)
      return 0;

    memset(dp, 0xfe, sizeof(dp));
    dp[0][0][1] = -prices[0];
    dp[0][0][0] = 0;

    int ans = 0;
    for (int i = 1; i < n; ++i) {
      for (int j = 0; j <= k; ++j) {
        dp[i][j][1] = std::max(dp[i - 1][j][1], dp[i - 1][j][0] - prices[i]);
        dp[i][j][0] = dp[i - 1][j][0];
        if (j)
          dp[i][j][0] =
              std::max(dp[i - 1][j - 1][1] + prices[i], dp[i - 1][j][0]);

        if (dp[i][j][0] > ans)
          ans = dp[i][j][0];
      }
    }
    return ans;
  }
};