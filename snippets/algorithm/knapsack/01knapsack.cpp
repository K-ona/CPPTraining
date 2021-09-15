// created by Kona @VSCode
// 01背包练习题：https://www.acwing.com/problem/content/280/
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <cstring>
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

int dp[10005]; 
int solve(int w[], int n, int m) {
  memset(dp, 0, sizeof dp); 
  dp[0] = 1; 
  for (int i = 1; i <= n; i++) {
    for (int j = m; j >= w[i]; --j) {
      dp[j] += dp[j - w[i]]; 
    }
  }
  return dp[m]; 
}

int w[105]; 
int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  int n, m;
  cin >> n >> m; 
  for (int i = 1; i <= n; i++) {
    cin >> w[i]; 
  }

  cout << solve(w, n, m) << endl; 
  return 0;
}