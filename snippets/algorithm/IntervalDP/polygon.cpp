// created by Kona @VSCode
// 区间dp练习题：https://www.acwing.com/problem/content/285/
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::queue;
using std::string;
using std::vector;

char op[105];
int val[105];
int dp[105][105][2];

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> op[i] >> val[i];
  }
  for (int j = n; j < 2 * n; ++j) {
    op[j] = op[j - n];
    val[j] = val[j - n];
  }

  for (int i = 0; i < 2 * n; i++)
    dp[i][i][0] = dp[i][i][1] = val[i];
  for (int len = 1; len < n; ++len) {
    for (int l = 0; l < 2 * n; ++l) {
      int r = l + len; 
      if (r >= 2 * n) 
        continue; 
      dp[l][r][0] = 0xcfcfcfcf;
      dp[l][r][1] = 0x3f3f3f3f;
      for (int k = l; k < r; ++k) {
        if (op[k + 1] == 't') {
          dp[l][r][0] = std::max(dp[l][r][0], dp[l][k][0] + dp[k + 1][r][0]);
          dp[l][r][1] = std::min(dp[l][r][1], dp[l][k][1] + dp[k + 1][r][1]);
        } else {
          int max = std::max(dp[l][k][0] * dp[k + 1][r][0], dp[l][k][1] * dp[k + 1][r][1]);
          int min = std::min(dp[l][k][0] * dp[k + 1][r][0],
                             std::min(dp[l][k][1] * dp[k + 1][r][0],
                                      std::min(dp[l][k][0] * dp[k + 1][r][1],
                                               dp[l][k][1] * dp[k + 1][r][1])));
          dp[l][r][0] = std::max(dp[l][r][0], max); 
          dp[l][r][1] = std::min(dp[l][r][1], min); 
        }
      }
    }
  }

  int res = 0xcfcfcfcf;
  for (int i = 0; i < n; i++) {
    res = std::max(res, dp[i][i + n - 1][0]);
  }
  cout << res << endl;
  for (int i = 0; i < n; i++) {
    if (dp[i][i + n - 1][0] == res) {
      cout << (i + 1) % n << " "; 
    }
  }
  return 0;
}