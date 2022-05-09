// 1. 记忆化搜索
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

// 2. dp
int dp[205][205]; 
class Solution {
 public:
  int minimumTotal(vector<vector<int>>& triangle) {
    memset(dp, 0x3f, sizeof(dp)); 
    int rows = triangle.size(); 
    int cols = triangle.back().size();
    for (int i = cols + 1; i >= 0; --i) dp[rows][i] = 0; 
    for (int i = rows - 1; i >= 0; --i) {
      for (int j = 0; j < triangle[i].size(); ++j) {
        dp[i][j] = std::min(dp[i + 1][j], dp[i + 1][1 + j]) + triangle[i][j];
      }
    }
    return dp[0][0];
  }
};

// 3. memory .opt dp

int dp[205]; 
class Solution {
 public:
  int minimumTotal(vector<vector<int>>& triangle) {
    memset(dp, 0, sizeof(dp)); 
    int rows = triangle.size(); 
    for (int i = rows - 1; i >= 0; --i) {
      int col = triangle[i].size();
      for (int j = 0; j < col; ++j) {
        if (dp[j + 1] < dp[j]) dp[j] = dp[j + 1]; 
        dp[j] += triangle[i][j];
      }
    }
    return dp[0];
  }
};