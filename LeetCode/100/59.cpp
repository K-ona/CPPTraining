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

void clockwise(vector<vector<int>>& matrix,
               int ltx,
               int lty,
               int n,
               int m,
               int& cnt) {
  if (n <= 0 or m <= 0)
    return;
  for (int i = 0; i < m; ++i) {
    matrix[ltx][lty + i] = cnt++;
  }
  for (int i = 1; i < n; ++i) {
    matrix[ltx + i][lty + m - 1] = cnt++;
  }
  if (n > 1)
    for (int i = m - 2; i >= 0; --i) {
     matrix[ltx + n - 1][lty + i] = cnt++;
    }
  if (m > 1)
    for (int i = n - 2; i > 0; --i) {
      matrix[ltx + i][lty] = cnt++;
    }
}

class Solution {
 public:
  vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> res(n, vector<int>(n, 0));
    int cnt = 1; 
    for (int i = 0, it_times = n / 2; i <= it_times; ++i) {
      clockwise(res, i, i, n - i - i, n - i - i, cnt);
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