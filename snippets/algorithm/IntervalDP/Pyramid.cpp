// created by Kona @VSCode
// 区间dp练习题：https://www.acwing.com/problem/content/description/286/
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

#include "string.h"

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::queue;
using std::string;
using std::vector;

ll dp[305][305];
constexpr int mod = 1e9;

int solve(std::string in) {
  memset(dp, 0, sizeof dp);
  int n = in.size();
  for (int i = 0; i < n; ++i) {
    dp[i][i] = 1;
  }
  for (int len = 1; len < n; ++len) {
    for (int l = 0; l + len < n; ++l) {
      for (int i = l + 1; i <= l + len; ++i) {
        if (in[i] == in[l])
          dp[l][l + len] =
              (dp[l][l + len] + (dp[l + 1][i - 1] * dp[i][l + len]) % mod) 
              % mod;
      }
    }
  }
  return dp[0][n - 1];
}

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  std::string in;
  cin >> in;

  cout << solve(in) << endl;
  return 0;
}