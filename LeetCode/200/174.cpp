int dp[205][205];
class Solution {
 public:
  int calculateMinimumHP(vector<vector<int>>& dungeon) {
    int n = dungeon.size();
    int m = dungeon[0].size();

    for (int i = n - 1; i >= 0; --i) {
      for (int j = m - 1; j >= 0; --j) {
        dp[i][j] = std::max(1, 1 - dungeon[i][j]);
        int res = 1e9;
        if (i != n - 1)
          res = std::min(dp[i + 1][j] - dungeon[i][j], res);
        if (j != m - 1)
          res = std::min(dp[i][j + 1] - dungeon[i][j], res);
        if (i != n - 1 or j != m - 1)
          dp[i][j] = std::max(res, 1);
      }
    }

    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < m; ++j) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    return dp[0][0];
  }
};