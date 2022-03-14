// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
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

class Solution1 {
  bool vis[10] = {false};
  void clear(bool vis[], bool val) {
    for (int i = 0; i < 9; ++i)
      vis[i] = val;
  }

 public:
  void solveSudoku(vector<vector<char>>& board) {
    std::stack<std::pair<int, int>> St;
    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        if (board[i][j] == '.')
          St.push({i, j});
      }
    }
    DFS(board, St);
  }

  bool DFS(vector<vector<char>>& board, std::stack<std::pair<int, int>>& St) {
    if (St.empty())
      return true;
    int n = St.top().first;
    int m = St.top().second;

    bool vis[10];
    bool avl[10];
    clear(vis, false);
    clear(avl, true);
    for (int i = 0; i < 9; ++i) {
      if (board[n][i] == '.')
        continue;
      if (vis[board[n][i] - '1'] == false)
        return false;
      vis[board[n][i] - '1'] = true;
    }
    for (int i = 0; i < 9; ++i)
      if (vis[i])
        avl[i] = false;

    clear(vis, false);
    for (int i = 0; i < 9; ++i) {
      if (board[i][m] == '.')
        continue;
      if (vis[board[i][m] - '1'] == false)
        return false;
      vis[board[i][m] - '1'] = true;
    }
    for (int i = 0; i < 9; ++i)
      if (vis[i])
        avl[i] = false;

    int ltr = n / 3 * 3;
    int ltc = m / 3 * 3;
    clear(vis, false);
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        if (board[ltr + i][ltc + j] == '.')
          continue;
        if (vis[board[ltr + i][ltc + j]] == true)
          return false;
        vis[board[ltr + i][ltc + j]] = true;
      }
    }
    for (int i = 0; i < 9; ++i)
      if (vis[i])
        avl[i] = false;

    St.pop();
    for (int i = 0; i < 9; ++i) {
      if (avl[i]) {
        board[n][m] = i + '1';
        if (DFS(board, St))
          return true;
        board[n][m] = '.';
      }
    }
    St.push({n, m});
    return false;
  }
};

class Solution {
 private:
  bool line[9][9];
  bool column[9][9];
  bool block[3][3][9];
  bool valid;
  vector<std::pair<int, int>> spaces;

 public:
  void dfs(vector<vector<char>>& board, int pos) {
    if (pos == spaces.size()) {
      valid = true;
      return;
    }

    auto [i, j] = spaces[pos];
    for (int digit = 0; digit < 9 && !valid; ++digit) {
      if (!line[i][digit] && !column[j][digit] && !block[i / 3][j / 3][digit]) {
        line[i][digit] = column[j][digit] = block[i / 3][j / 3][digit] = true;
        board[i][j] = digit + '0' + 1;
        dfs(board, pos + 1);
        line[i][digit] = column[j][digit] = block[i / 3][j / 3][digit] = false;
      }
    }
  }

  void solveSudoku(vector<vector<char>>& board) {
    memset(line, false, sizeof(line));
    memset(column, false, sizeof(column));
    memset(block, false, sizeof(block));
    valid = false;

    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        if (board[i][j] == '.') {
          spaces.emplace_back(i, j);
        } else {
          int digit = board[i][j] - '0' - 1;
          line[i][digit] = column[j][digit] = block[i / 3][j / 3][digit] = true;
        }
      }
    }

    dfs(board, 0);
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