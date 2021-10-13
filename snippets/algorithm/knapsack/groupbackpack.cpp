// created by Kona @VSCode
// 分组背包简单题：https://www.acwing.com/problem/content/9/
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

int v[105][105];
int w[105][105]; 
int cnt[105]; 
int dp[105]; 

int solve(int n, int V, int v[][105], int w[][105]) {
  ::memset(dp, 0xcf, sizeof dp); 
  dp[0] = 0; 
  for (int i = 0; i < n; ++i) {
    for (int j = V; j >= 0; --j) {
      for (int k = 0; k < cnt[i]; ++k) {
        if (j >= v[i][k]) dp[j] = std::max(dp[j], dp[j - v[i][k]] + w[i][k]); 
      }
    }
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
  for (int i = 0; i < n && cin >> cnt[i]; ++i) {
    for (int j = 0; j < cnt[i]; ++j) {
      cin >> v[i][j] >> w[i][j]; 
    }
  }
  cout << solve(n, V, v, w) << endl; 

  return 0;
}