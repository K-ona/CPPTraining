// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
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
 public:
  bool isValidSudoku(vector<vector<char>>& board) {
    bool flag = true;
    bool vis[10] = {false};
    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j)
        vis[j] = false;
      for (int j = 0; j < 9; ++j) {
        if (board[i][j] == '.')
          continue;
        if (vis[board[i][j] - '1'])
          { return false; }
        vis[board[i][j] - '1'] = true;
      }

      for (int j = 0; j < 9; ++j)
        vis[j] = false;
      for (int j = 0; j < 9; ++j) {
        if (board[j][i] == '.')
          continue;
        if (vis[board[j][i] - '1'])
        {  return false; }
        vis[board[j][i] - '1'] = true;
      }

      if (i + 2 < 9) {
        for (int j = 0; j < 7; ++j) {
          if (i % 3 or j % 3) continue;
          for (int k = 0; k < 9; ++k)
            vis[k] = false;
          for (int n = 0; n < 3; ++n) {
            for (int m = 0; m < 3; ++m) {
              if (board[i + n][j + m] == '.')
                continue;
              if (vis[board[i + n][j + m] - '1'])
                {  return false; }
              vis[board[i + n][j + m] - '1'] = true;
            }
          }
        }
      }
    }
    return true;
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