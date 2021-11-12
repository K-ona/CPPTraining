// created by Kona @VSCode
// 状压dp例题：https://www.acwing.com/problem/content/293/

// 状压dp常见做法有两种
// 1. 枚举+合法性判断
// 2. 生成: 生成合法的状态，常用于比较繁琐、复杂的状态转移
// 本例选择第一种做法
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

ll dp[20][2100]; 
bool invalid[2100]; 

void init(int m) {
  for (int i = 0; i < 1 << m; ++i) {
    bool cnt = 0, has_odd = 0; 
    for (int j = 0; j < m; ++j) {
      if (i >> j & 1) {
        has_odd |= cnt;
        cnt = 0; 
      } else {
        cnt ^= 1;
      }
    }
    invalid[i] = has_odd | cnt;
  }
}

ll solve(int n, int m) {
  ::memset(dp, 0, sizeof dp); 
  dp[0][0] = 1; 
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < 1 << m; ++j) {
      for (int k = 0; k < 1 << m; ++k) {
        if ( (j bitand k) == 0 and !invalid[j bitor k]) {
          dp[i][j] += dp[i - 1][k]; 
        }
      }
    }
  }
  return dp[n][0];
}

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  int n, m; 
  while (cin >> n >> m && n && m) {
    init(m); 
    cout << solve(n, m) << endl; 
  }
  return 0;
}