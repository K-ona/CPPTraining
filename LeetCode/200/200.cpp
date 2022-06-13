int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
int n, m;
int vis[300 * 300];

class Solution {
 public:
  int numIslands(vector<vector<char>>& grid) {
    n = grid.size();
    m = grid[0].size();
    int cnt = 0;
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (grid[i][j] == '1' && !vis[i * 300 + j])
          ++cnt, bfs(grid, i * 300 + j);
      }
    }
    return cnt;
  }

  void bfs(vector<vector<char>>& grid, int pos) {
    std::queue<int> Q;
    Q.push(pos);
    vis[pos] = 1;
    while (!Q.empty()) {
      int x = Q.front() / 300;
      int y = Q.front() % 300;
      Q.pop();
      for (int i = 0; i < 4; ++i) {
        int tx = x + dx[i];
        int ty = y + dy[i];
        if (tx < 0 || tx >= n || ty < 0 || ty >= m)
          continue;
        pos = tx * 300 + ty;
        if (!vis[pos] && grid[tx][ty] == '1')
          Q.push(pos), vis[pos] = 1;
      }
    }
  }
};