// created by Kona @VSCode
// 线性dp练习题：https://www.acwing.com/problem/content/277/
#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;

int dp[105][55][55];
int solve(int pref[][55], int n, int m) {
  memset(dp, -1, sizeof dp);
  dp[0][1][1] = 0;
  for (int len = 1; len < n + m - 1; ++len) {
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (len == n + m - 2 && i + j == 2 * n) {
        } else if (i == j)
          continue;
        int iy = len - i + 2;
        int jy = len - j + 2;
        if (iy < 1 || iy > m || jy < 1 || jy > m) continue; 
        if (-1 != dp[len - 1][i][j])
          dp[len][i][j] = std::max(
              dp[len][i][j], dp[len - 1][i][j] + pref[i][iy] + pref[j][jy]);
        if (-1 != dp[len - 1][i - 1][j - 1])
          dp[len][i][j] =
              std::max(dp[len][i][j], 
                        dp[len - 1][i - 1][j - 1] + pref[i][iy] + pref[j][jy]);
        if (-1 != dp[len - 1][i][j - 1])
          dp[len][i][j] = std::max(
              dp[len][i][j], dp[len - 1][i][j - 1] + pref[i][iy] + pref[j][jy]);
        if (-1 != dp[len - 1][i - 1][j])
          dp[len][i][j] = std::max(
              dp[len][i][j], dp[len - 1][i - 1][j] + pref[i][iy] + pref[j][jy]);
      }
    }
  }
  return dp[n + m - 2][n][n];
}

int pref[55][55];
int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> pref[i][j];
    }
  }

  cout << solve(pref, n, m) << endl;

  return 0;
}