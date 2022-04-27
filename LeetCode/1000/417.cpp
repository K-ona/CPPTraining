int cnt[205][205]; 
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
bool vis[205][205]; 

#include <vector>
#include <cstring>
#include <iostream>

using std::vector; 

class Solution {
    int n, m;
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        n = heights.size(); 
        m = heights[0].size(); 
        memset(cnt, 0, sizeof(cnt)); 
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) { 
                memset(vis, 0, sizeof(vis)); 
                dfs(i, j, heights); 
            }
        }
        vector<vector<int>> ans; 
        ans.reserve(n * m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (cnt[i][j] == 3)
                    ans.emplace_back(vector<int>{i, j});
            }
        }
        return ans; 
    }

    int dfs(int x, int y, vector<vector<int>>& heights) {
        vis[x][y] = true; 
        int res = 0; 
        for (int i = 0; i < 4; ++i) {
            int tx = x + dx[i];
            int ty = y + dy[i];
            if (tx < 0 or ty < 0) {
                res |= 1; 
            } else if (tx >= n or ty >= m){
                res |= 2;
            } else if (heights[tx][ty] <= heights[x][y] and !vis[tx][ty]) {
                res |= dfs(tx, ty, heights); 
            }
        }
        return cnt[x][y] |= res; 
    }
};

int main() {
  
  // Solution().pacificAtlantic({{1,2,2,3,5},{3,2,3,4,4},{2,4,5,3,1},{6,7,1,4,5},{5,1,1,2,4}}); 
  return 0; 
}