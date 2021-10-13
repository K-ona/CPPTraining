// created by Kona @VSCode
// 区间dp例题：https://www.acwing.com/problem/content/284/
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

int c[1005];
int sum[1005]; 

int dp[1005][1005];
int solve(int c[], int n) {
  memset(dp, 0x3f, sizeof dp); 
  for (int i = 1; i <= n; ++i) dp[i][i] = 0; 
  for (int len = 1; len < n; ++len) {
    for (int l = 1; l + len <= n; ++l) {
      for (int k = l; k < l + len; ++k) {
        dp[l][l + len] = std::min(dp[l][l + len], dp[l][k] + dp[k + 1][l + len]); 
      }
      dp[l][l + len] += sum[l + len] - sum[l - 1];
    }
  }
  return dp[1][n]; 
}

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> c[i]; 
    sum[i] = sum[i - 1] + c[i]; 
  }
  cout << solve(c, n) << endl; 
  return 0;
}