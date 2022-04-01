// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>

#include <string.h>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::queue;
using std::string;
using std::vector;

class Solution {
    int dx[2] = {1, 0}; 
    int dy[2] = {0, 1}; 
    int mem[205][205]; 
public:
    int minPathSum(vector<vector<int>>& grid) {
        memset(mem, -1, sizeof(mem)); 
        return DFS(grid, 0, 0); 
    }
    int DFS(vector<vector<int>>& grid, int n, int m) {
        if (~mem[n][m]) return mem[n][m]; 
        if (n == grid.size() - 1 and m == grid[0].size() - 1) 
            return mem[n][m] = grid[n][m]; 
        int res = INT32_MAX;
        for (int i = 0; i < 2; ++i) {
            int x = dx[i] + n; 
            int y = dy[i] + m; 
            if (x >= grid.size() or y >= grid[0].size()) continue; 
            res = std::min(DFS(grid, x, y), res); 
        }
        return mem[n][m] = res + grid[n][m]; 
    }
};


int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  return 0;
}