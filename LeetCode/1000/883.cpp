class Solution {
  int maxr = 0;
  int maxc = 0;
  int row = 0;

 public:
  int projectionArea(vector<vector<int>>& grid) {
    row = grid.size();
    int res = 0;
    for (int i = 0; i < row; ++i) {
      maxr = 0;
      maxc = 0;
      for (int j = 0; j < row; ++j) {
        maxr = std::max(grid[i][j], maxr);
        maxc = std::max(grid[j][i], maxc);
        res += grid[i][j] != 0;
      }
      res += maxr + maxc;
    }
    return res;
  }
};