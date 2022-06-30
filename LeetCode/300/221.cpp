class Solution {
 public:
  int maximalSquare(vector<vector<char>>& matrix) {
    int n = matrix.size(), m = matrix[0].size();
    vector<vector<int>> height(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (matrix[i][j] == '1')
          height[i][j] = (j ? height[i][j - 1] + 1 : 1);
        else
          height[i][j] = 0;
      }
    }

    int ans = 0;
    for (int j = m - 1; ~j; --j) {
      stack<int> stk;
      vector<int> bottom(n, n);
      for (int i = 0; i < n; ++i) {
        if (stk.empty() || height[stk.top()][j] <= height[i][j])
          stk.push(i);
        else {
          while (!stk.empty() && height[stk.top()][j] > height[i][j]) {
            bottom[stk.top()] = i;
            stk.pop();
          }
          stk.push(i);
        }
      }
      stk = stack<int>{};
      vector<int> up(n, -1);
      for (int i = n - 1; ~i; --i) {
        if (stk.empty() || height[stk.top()][j] <= height[i][j])
          stk.push(i);
        else {
          while (!stk.empty() && height[stk.top()][j] > height[i][j]) {
            up[stk.top()] = i;
            stk.pop();
          }
          stk.push(i);
        }
      }

      for (int i = 0; i < n; ++i) {
        int len = std::min(height[i][j], bottom[i] - up[i] - 1);
        // cout << height[i][j] << " " << bottom[i] << " " << up[i] << endl;
        ans = std::max(ans, len * len);
      }
    }
    return ans;
  }
};