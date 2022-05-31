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
  int dx[4]{-1, 1, 0, 0}; 
  int dy[4]{0, 0, 1, -1}; 
  bool vis[205][205]; 
  int n, m, l; 
 public:
  bool exist(vector<vector<char>>& board, string& word) {
    n = board.size(); 
    m = board[0].size(); 
    l = word.size(); 
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (board[i][j] == word[0]) {
          memset(vis, 0, sizeof(vis)); 
          vis[i][j] = true; 
          if (DFS(board, i, j, 1, word)) return true; 
        }
      }
    }
    return false; 
  }

  bool DFS(vector<vector<char>>& board, int x, int y, int len, string& word) {
    if (len == l) return true;
    for (int i = 0; i < 4; ++i) {
      int tmpx = dx[i] + x; 
      int tmpy = dy[i] + y; 
      if (tmpx < 0 or tmpx >= n or tmpy < 0 or tmpy >= m) continue;
      if (vis[tmpx][tmpy]) continue; 
      if (board[tmpx][tmpy] == word[len]) {
        vis[tmpx][tmpy] = true; 
        if (DFS(board, x + dx[i], y + dy[i], len + 1, word)) return true; 
        vis[tmpx][tmpy] = false; 
      }
    }
    return false; 
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