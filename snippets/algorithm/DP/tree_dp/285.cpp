// created by Kona @VSCode
// 最简单的树形DP：https://www.acwing.com/problem/content/description/287/
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

bool vis[6005]; 
int H[6005]; 
int dp[6005][2]; 
vector<int> G[6005]; 

void DFS(int u) {
  dp[u][0] = 0;
  dp[u][1] = H[u];
  for (int v: G[u]) {
    DFS(v); 
    dp[u][0] += std::max(dp[v][0], dp[v][1]); 
    dp[u][1] += dp[v][0]; 
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  int N; 
  cin >> N; 
  for (int i = 1; i <= N; ++i) {
    cin >> H[i]; 
  }

  for (int i = 1, u, v; i < N; ++i) {
    cin >> u >> v; 
    G[v].push_back(u); 
    vis[u] = true; 
  }

  for (int i = 1; i <= N; ++i) {
    if (!vis[i]) {
      DFS(i); 
      cout << std::max(dp[i][0], dp[i][1]) << endl; 
      break; 
    }
  }
  return 0;
}