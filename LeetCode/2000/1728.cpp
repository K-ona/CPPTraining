int dx[] = {0, 0, -1, 1, 0};
int dy[] = {1, -1, 0, 0, 0};
int n, m;
int cx, cy, mx, my;
int catJump, mouseJump;
int vis[1005][8][8][8][8];
class Solution {
 public:
  bool canMouseWin(vector<string>& grid, int catJump, int mouseJump) {
    n = grid.size();
    m = grid[0].size();
    ::catJump = catJump;
    ::mouseJump = mouseJump;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (grid[i][j] == 'C') {
          cx = i;
          cy = j;
          grid[i][j] = '.';
        }
        if (grid[i][j] == 'M') {
          mx = i;
          my = j;
          grid[i][j] = '.';
        }
      }
    }
    memset(vis, -1, sizeof(vis));
    return dfs(grid, mx, my, cx, cy, 1);
  }

  bool dfs(vector<string>& grid, int mx, int my, int cx, int cy, int steps) {
    if (grid[cx][cy] == 'F')
      return vis[steps][mx][my][cx][cy] = 0;
    if (grid[mx][my] == 'F')
      return vis[steps][mx][my][cx][cy] = 1;
    if (steps >= 150)
      return vis[steps][mx][my][cx][cy] = 0;
    if (mx == cx and cy == my)
      return vis[steps][mx][my][cx][cy] = 0;

    if (~vis[steps][mx][my][cx][cy])
      return vis[steps][mx][my][cx][cy];

    if (steps & 1) {
      for (int i = 0; i < 5; ++i) {
        for (int j = 1; j <= mouseJump; ++j) {
          int tx = mx + j * dx[i];
          int ty = my + j * dy[i];
          if (tx < 0 or tx >= n or ty < 0 or ty >= m)
            break;
          if (grid[tx][ty] == '#')
            break;
          if (dfs(grid, tx, ty, cx, cy, steps + 1))
            return vis[steps][mx][my][cx][cy] = 1;
        }
      }
      return vis[steps][mx][my][cx][cy] = 0;
    } else {
      for (int i = 0; i < 5; ++i) {
        for (int j = 1; j <= catJump; ++j) {
          int tx = cx + j * dx[i];
          int ty = cy + j * dy[i];
          if (tx < 0 or tx >= n or ty < 0 or ty >= m)
            break;
          if (grid[tx][ty] == '#')
            break;
          if (!dfs(grid, mx, my, tx, ty, steps + 1))
            return vis[steps][mx][my][cx][cy] = 0;
        }
      }
      return vis[steps][mx][my][cx][cy] = 1;
    }
    return false;
  }
};