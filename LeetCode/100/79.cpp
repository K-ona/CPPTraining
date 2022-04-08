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
  int dx[4] = {1, 0, -1, 0};
  int dy[4] = {0, 1, 0, -1};
  bool vis[10][10];
 public:
  bool exist(vector<vector<char>>& board, string word) {
    memset(vis, false, sizeof(vis));
    int n = board.size();
    int m = board[0].size();
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (board[i][j] == word[0]) {
          vis[i][j] = true;
          if (DFS(board, word, i, j, 1)) return true;
          vis[i][j] = false;
        }
      }
    }
    return false; 
  }

  bool DFS(vector<vector<char>>& board, string word, int x, int y, int pos) {
    if (pos == word.size()) return true;
    bool res = false;
    for (int i = 0; i < 4; ++i) {
      if (x + dx[i] < 0 || x + dx[i] >= board.size() ||
          y + dy[i] < 0 || y + dy[i] >= board[0].size())
        continue;
      if (board[x + dx[i]][y + dy[i]] == word[pos] and !vis[x + dx[i]][y + dy[i]]) {
        vis[x + dx[i]][y + dy[i]] = true;
        res |= DFS(board, word, x + dx[i], y + dy[i], pos + 1);
        if (res) return res; 
        vis[x + dx[i]][y + dy[i]] = false;
      }
    }
    return res; 
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