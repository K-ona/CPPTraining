// created by Kona @VSCode
// 树上分组背包：https://www.acwing.com/problem/content/description/288/
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
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

int n, m; 
vector<int> G[305]; 
int v[305]; 
int dp[305][305]; 

void solve(int u) {
  dp[u][0] = 0;
  for (auto v: G[u]) {
    solve(v); 
    for (int k = m; k; --k) {
      for (int i = 0; i <= k; ++i) {
        dp[u][k] = std::max(dp[u][k], dp[u][k - i] + dp[v][i]); 
      }
    }
  }
  if (u) {
    for (int i = m; i; --i) {
      dp[u][i] = dp[u][i - 1] + v[u];
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  cin >> n >> m; 
  for (int i = 1, pre; i <= n; ++i) {
    cin >> pre >> v[i]; 
    G[pre].push_back(i); 
  }
  solve(0); 
  cout << dp[0][m] << endl; 
  return 0;
}