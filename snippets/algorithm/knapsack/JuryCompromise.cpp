// created by Kona @VSCode
// 01背包练习题：https://www.acwing.com/problem/content/description/282/
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

int d[205], p[205]; 
int dp[25][805];
bool fa[205][25][805];

int D, P; 
void print(int i, int j, int k) {
  if (i && j)
  for (int u = i; u; --u) {
    if (fa[u][j][k + 400]) {
      D += d[u]; 
      P += p[u]; 
      print(u - 1, j - 1, k - d[u] + p[u]);
      cout << " " << u; 
      break; 
    }
  }
  else cout << "Best jury has value " << P <<" for prosecution and value " << D <<" for defence:" << endl; 
}

int solve(int p[], int d[], int n, int m) {
  memset(dp, 0xcf, sizeof dp);
  memset(fa, 0, sizeof fa); 
  D = P = 0; 
  dp[0][0 + 400] = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = m; j; --j) {
      for (int s = -20 * m; s <= 20 * m; ++s) {
        if (s - d[i] + p[i] < -20 * m || s - d[i] + p[i] > 20 * m)
          continue;
        dp[j][s + 400] = std::max(
            dp[j][s + 400], dp[j - 1][400 + s - d[i] + p[i]] + d[i] + p[i]);
        if (dp[j][s + 400] == dp[j - 1][400 + s - d[i] + p[i]] + d[i] + p[i])
          fa[i][j][s + 400] = true;
      }
    }
  }
  int max = INT32_MIN;
  int pre = 450; 
  int anss = 0; 
  for (int s = -20 * m; s <= 20 * m; ++s) {
    if (dp[m][s + 400] >= 0 &&
        (abs(s) < pre || (dp[m][s + 400] > max && abs(s) == pre))) {
      max = dp[m][s + 400];
      pre = abs(s); 
      anss = s; 
    }
  }

  print(n, m, anss); 
  // cout << pre << " " << max << endl;
  cout << endl; 
  return max;
}




int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  int n, m;
  int t = 1; 
  while (cin >> n >> m && n + m) {
    for (int i = 1; i <= n; ++i) {
      cin >> p[i] >> d[i];
    }
    cout << "Jury #" << t++ << "\n";
    solve(p, d, n, m);
  }

  return 0;
}