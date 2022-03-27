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
 public:
  int totalNQueens(int n) {
    vector<vector<string>> res;
    vector<string> board(n, string(n, '.'));
    vector<int> col(n, 0);
    vector<int> dia1(2 * n - 1, 0);
    vector<int> dia2(2 * n - 1, 0);
    vector<int> row(n, 0);
    dfs(res, board, col, dia1, dia2, row, 0);
    return res.size();
  }
  void dfs(vector<vector<string>>& res,
           vector<string>& board,
           vector<int>& col,
           vector<int>& dia1,
           vector<int>& dia2,
           vector<int>& row,
           int i) {
    if (i == board.size()) {
      res.push_back(board);
      return;
    }
    for (int j = 0; j < board.size(); ++j) {
      if (col[j] || dia1[i + j] || dia2[i - j + board.size() - 1])
        continue;
      board[i][j] = 'Q';
      col[j] = dia1[i + j] = dia2[i - j + board.size() - 1] = 1;
      row[i] = 1;
      dfs(res, board, col, dia1, dia2, row, i + 1);
      board[i][j] = '.';
      col[j] = dia1[i + j] = dia2[i - j + board.size() - 1] = 0;
      row[i] = 0;
    }
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