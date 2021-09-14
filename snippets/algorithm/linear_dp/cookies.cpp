// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cstring>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;

int sum[35], ind[35];
int dp[35][5005];
int ans[35]; 
int solve(int g[], int n, int m) {
  for (int i = 0; i <= n; i++)
    ind[i] = i;

  std::sort(ind + 1, ind + n + 1,
            [&g](int a, int b) -> bool { return g[a] > g[b]; });

  for (int i = 1; i <= n; i++) {
      sum[i] = sum[i - 1] + g[ind[i]]; 
  }
  memset(dp, 0x3f, sizeof dp); 
  dp[0][0] = 0; 
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (i <= j)
        dp[i][j] = dp[i][j - i];
      for (int k = 1; k <= i && k <= j; ++k) {
        dp[i][j] = std::min(dp[i][j], dp[i - k][j - k] + (i - k) * (sum[i] - sum[i - k])); 
      }
    }
  }

  int i = n, j = m, h = 0;
  while (i && j) {
      if (i <= j && dp[i][j] == dp[i][j - i]) j -= i, ++h; 
      else {
          for (int k = 1; k <= i && k <= j; ++k) {
              if (dp[i][j] == dp[i - k][j - k] + (i - k) * (sum[i] - sum[i - k])) {
                for (int u = i; u > i - k; --u) 
                  ans[ind[u]] = 1 + h; 
                i -= k; j -= k; 
                break; 
              }
          }
      }
  }

  return dp[n][m]; 
}

int g[35];
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
    cin >> g[i];
  }

  cout << solve(g, n, m) << endl; 
  for (int i = 1; i <= n; ++i) {
      cout << ans[i] << " "; 
  }
  cout << endl; 
  return 0;
}