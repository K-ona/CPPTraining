// created by Kona @VSCode
// 多重背包模板题：
// 二进制优化：https://www.acwing.com/problem/content/description/5/
// 暴力拆分：https://www.acwing.com/problem/content/4/
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>

#include <string.h>

#include "knapsack.h"

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::queue;
using std::string;
using std::vector;

int v[1005]; 
int w[1005]; 
int s[1005];
int dp[2005];

void update_mul(int V, int v, int w, int s, int dp[]) {
  int k = 0;
  for (; (1 << (k + 1)) - 1 <= s; ++k) {
    for (int j = V; j >= (1 << k) * v; --j) {
      dp[j] = std::max(dp[j], dp[j - (1 << k) * v] + (1 << k) * w);
    }
  }
  int R = s - (1 << k) + 1;
  if (R)
    for (int j = V; j >= R * v; --j) {
      dp[j] = std::max(dp[j], dp[j - R * v] + R * w);
    }
}

// 暴力拆分为01背包
int solve(int N, int V, int v[], int w[], int s[]) {
  ::memset(dp, 0xcf, sizeof dp); 
  dp[0] = 0; 
  for (int i = 1; i <= N; ++i) {
    for (int k = 0; k < s[i]; ++k) {
      for (int j = V; j >= v[i]; --j) {
        dp[j] = std::max(dp[j], dp[j - v[i]] + w[i]); 
      }
    }
  }
  return *std::max_element(dp, dp + V + 1);
}

// 二进制优化拆分
int bit_solve(int N, int V, int v[], int w[], int s[]) {
  ::memset(dp, 0xcf, sizeof dp);
  dp[0] = 0;
  for (int i = 1; i <= N; ++i) {
    KonaImpl::knapsack::update_mul_bibit(V, v[i], w[i], s[i], dp); 
  }
  return *std::max_element(dp, dp + V + 1);
}

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */
  int n, V; 
  cin >> n >> V; 
  for (int i = 1; i <= n; ++i) {
    cin >> v[i] >> w[i] >> s[i]; 
  }

  cout << bit_solve(n, V, v, w, s) << endl; 
  return 0;
}