#include <vector>
#include <queue>
#include <algorithm>

using std::sort; 
using std::vector; 
using std::priority_queue; 

class Solution {
 public:
  int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

  int bfs(vector<vector<int>>& forest, int sx, int sy, int tx, int ty) {
    if (sx == tx and ty == sy) return 0; 
    int row = forest.size();
    int col = forest[0].size();

    vector<vector<int>> costed(row, vector<int>(col, INT_MAX)); 
    priority_queue<std::tuple<int, int, int>, vector<std::tuple<int, int, int>>, std::greater<std::tuple<int, int, int>>> PQ;
    costed[sx][sy] = abs(sx - tx) + abs(sy - ty);  
    PQ.emplace(costed[sx][sy], 0, sx * col + sy); 
    while (!PQ.empty()) {
      auto [cost, dist, loc] = PQ.top(); 
      PQ.pop(); 
      int cx = loc / col; 
      int cy = loc % col; 
      if (cx == tx and cy == ty) return dist; 
      for (int i = 0; i < 4; ++i) {
        int nx = cx + dirs[i][0]; 
        int ny = cy + dirs[i][1]; 
        if (nx < 0 or nx >= row or ny < 0 or ny >= col or forest[nx][ny] == 0) continue;

        int ncost = dist + 1 + abs(nx - tx) + abs(ny - ty); 
        if (ncost < costed[nx][ny]) {
          PQ.emplace(ncost, dist + 1, nx * col + ny);
          costed[nx][ny] = ncost;
        }
      }
    }
    return -1; 
  }

  int cutOffTree(vector<vector<int>>& forest) {
    vector<pair<int, int>> trees;
    int row = forest.size();
    int col = forest[0].size();
    for (int i = 0; i < row; ++i) {
      for (int j = 0; j < col; ++j) {
        if (forest[i][j] > 1) {
          trees.emplace_back(i, j);
        }
      }
    }
    sort(trees.begin(), trees.end(),
         [&](const pair<int, int>& a, const pair<int, int>& b) {
           return forest[a.first][a.second] < forest[b.first][b.second];
         });

    int cx = 0;
    int cy = 0;
    int ans = 0;
    for (int i = 0; i < trees.size(); ++i) {
      int steps = bfs(forest, cx, cy, trees[i].first, trees[i].second);
      if (steps == -1) {
        return -1;
      }
      ans += steps;
      cx = trees[i].first;
      cy = trees[i].second;
    }
    return ans;
  }
};
