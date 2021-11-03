// created by Kona @VSCode
// 环状dp与后效性处理：https://www.acwing.com/problem/content/description/290/
// 处理环状结构的后效性
// 本题是通过头尾之间的限制关系，分别讨论求解，避免枚举起点
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

int a[4000];
int dp[2][4000][2];

int solve(int (&a)[4000], int (&dp)[2][4000][2], int n, int b) {
  memset(dp, 0xcf, sizeof dp);
  dp[0][0][0] = 0; dp[0][1][1] = 0; 
  for (int i = 1; i < n; ++i) {
      dp[i & 1][0][0] = dp[(i - 1) & 1][0][0];
    for (int j = 0; j < b; ++j) {
      dp[i & 1][j + 1][0] = std::max(dp[(i - 1) & 1][j + 1][0], dp[(i - 1) & 1][j + 1][1]);
      dp[i & 1][j + 1][1] = std::max(dp[(i - 1) & 1][j][0], dp[(i - 1) & 1][j][1] + a[i]);
    }
  }
  int res = std::max(dp[(n - 1) & 1][b][0], dp[(n - 1) & 1][b][1]); 
  
  // cout << res << endl; 
  
  memset(dp, 0xcf, sizeof dp); 
  dp[0][1][1] = a[0]; 
  for (int i = 1; i < n; ++i) {
      dp[i & 1][0][0] = dp[(i - 1) & 1][0][0];
    for (int j = 0; j < b; ++j) {
      dp[i & 1][j + 1][0] = std::max(dp[(i - 1) & 1][j + 1][0], dp[(i - 1) & 1][j + 1][1]);
      dp[i & 1][j + 1][1] = std::max(dp[(i - 1) & 1][j][0], dp[(i - 1) & 1][j][1] + a[i]);
    }
  }
  return std::max(res, dp[(n - 1) & 1][b][1]); 
}

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  int n, b;
  cin >> n >> b;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  cout << solve(a, dp, n, b) << endl;

  return 0;
}