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
  int mem[105][105];
  int dx[2] = {1, 0};
  int dy[2] = {0, 1};
public:
  int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    memset(mem, -1, sizeof(mem)); 
    if (!obstacleGrid[0][0])
        return DFS(0, 0, obstacleGrid);
    else return 0; 
  }
  int DFS(int x, int y, vector<vector<int>>& obstacleGrid) {
    /* code */
    if (x == obstacleGrid.size() - 1 and y == obstacleGrid[0].size() - 1) {
      return 1;
    }
    if (mem[x][y] != -1) {
      return mem[x][y];
    }
    int res = 0; 
    for (int i = 0; i < 2; ++i) {
      int tmpx = x + dx[i];
      int tmpy = y + dy[i];
      if (tmpx < 0 or tmpx >= obstacleGrid.size() or tmpy < 0 or tmpy >= obstacleGrid[0].size() or obstacleGrid[tmpx][tmpy]) {
        continue;
      }
      res += DFS(tmpx, tmpy, obstacleGrid); 
    }
    return mem[x][y] = res;
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