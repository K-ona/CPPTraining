// created by Kona @VSCode
// 利用阶段可以确定一个位置优化掉一维，即状态各维度线性无关
// 再用滚动数组减少空间
// 注意滚动数组时对用过的数组进行恢复
// 题目地址：https://www.acwing.com/problem/content/276/
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

int dis[205][205];
int r[1005];

int dp[2][205][205];
int solve(int dis[][205], int L, int r[], int n) {
  ::memset(dp, 0x3f, sizeof dp);
  r[0] = 3;
  dp[0][1][2] = 0;
  // int ind = 0;
  for (int i = 1; i <= n; ++i) {
    for (int a = 1; a <= L; ++a) {
      for (int b = 1; b <= L; ++b) {
        if (dp[i - 1 & 1][a][b] == 0x3f3f3f3f) continue; 
        if (a != r[i] && b != r[i])
          dp[i & 1][a][b] =
              std::min(dp[i & 1][a][b], dp[i - 1 & 1][a][b] + dis[r[i - 1]][r[i]]);
        if (r[i - 1] != r[i] && b != r[i])
          dp[i & 1][r[i - 1]][b] =
              std::min(dp[i & 1][r[i - 1]][b], dp[i - 1 & 1][a][b] + dis[a][r[i]]);
        if (r[i] != a && r[i - 1] != r[i])
          dp[i & 1][a][r[i - 1]] =
              std::min(dp[i & 1][a][r[i - 1]], dp[i - 1 & 1][a][b] + dis[b][r[i]]);
        dp[i - 1 & 1][a][b] = 0x3f3f3f3f; 
      }
    }
  }
  // for (int i = 1; i <= L; ++i) {
  //   for (int j = 1; j <= L; ++j) {
  //     cout << dp[n & 1][i][j] << " "; 
  //   }
  //   cout << endl; 
  // }
  return *std::min_element(&dp[n & 1][1][1], &dp[n & 1][L][L] + 1);
}

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  int L, n;
  cin >> L >> n;
  for (int i = 1; i <= L; ++i) {
    for (int j = 1; j <= L; ++j) {
      cin >> dis[i][j];
    }
  }

  for (int i = 1; i <= n; ++i) {
    cin >> r[i];
  }

  cout << solve(dis, L, r, n) << endl;
  return 0;
}