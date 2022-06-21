class Solution {
 public:
  vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
    int n = mat.size(); 
    int m = mat[0].size(); 
    int x = 0, y = 0;
    vector<int> res;
    res.reserve(n * m);
    for (int cnt = 0; cnt < n + m; ++cnt) {
      if (cnt & 1) {
        if (cnt < m) y = cnt, x = 0; 
        else y = m - 1, x = cnt - y;

        while (x < n && y >= 0) res.push_back(mat[x++][y--]);

      } else {
        if (cnt < n) x = cnt, y = 0;
        else x = n - 1, y = cnt - x; 

        while (x >= 0 && y < m) res.push_back(mat[x--][y++]);

      }
    }
    return res; 
  }
};