int dp[205][205];
class Solution {
  int rows;
  int ans; 

 public:
  int minimumTotal(vector<vector<int>>& triangle) {
    rows = triangle.size(); 
    ans = 1e9; 
    memset(dp, 0x3f, sizeof(dp)); 
    dfs(0, 0, 0, triangle); 
    return ans; 
  }

  int dfs(int row, int i, int sum, vector<vector<int>>& triangle) {
    if (row == rows) {
      ans = std::min(ans, sum); 
      return 0;
    }
    if (0x3f3f3f3f != dp[row][i]) {
      ans = std::min(ans, sum + dp[row][i]);
      return dp[row][i]; 
    }

    int res = 1e9; 
    res = std::min(res, dfs(row + 1, i, sum + triangle[row][i], triangle)); 
    res = std::min(res, dfs(row + 1, 1 + i, sum + triangle[row][i], triangle)); 
    return dp[row][i] = res + triangle[row][i];
  }
};
