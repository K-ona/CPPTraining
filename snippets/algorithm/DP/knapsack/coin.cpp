// created by Kona @VSCode
// 背包练习题：https://www.acwing.com/problem/content/283/
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

int A[105]; 
int C[105]; 

bool dp[100005];
int uesd[100005]; 
int solve(int n, int m, int A[], int C[]) {
  memset(dp, 0, sizeof dp); 
  dp[0] = true; 
  for (int i = 0; i < n; ++i) {
    memset(uesd, 0, sizeof uesd); 
    for (int j = A[i]; j <= m; ++j) {
      if (!dp[j] && dp[j - A[i]] && uesd[j - A[i]] < C[i]) {
        dp[j] = true; 
        uesd[j] = uesd[j - A[i]] + 1; 
      }
    }
  }
  int res = 0; 
  for (int i = 1; i <= m; ++i) {
    res += static_cast<int>(dp[i]); 
  }
  return res; 
}

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  int n, m; 
  while (cin >> n >> m && n) {
    for (int i = 0; i < n; ++i) {
      cin >> A[i]; 
    }
    for (int i = 0; i < n; ++i) {
      cin >> C[i]; 
    }
    cout << solve(n, m, A, C) << endl; 
  }
  return 0;
}