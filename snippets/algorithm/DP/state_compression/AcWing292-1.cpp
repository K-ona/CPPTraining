// created by Kona @VSCode
// 状压dp例题：https://www.acwing.com/problem/content/description/294/

// 状压dp常见做法有两种
// 1. 枚举+合法性判断
// 2. 生成: 生成合法的状态，常用于比较繁琐、复杂的状态转移

// 本例选择第1种做法
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
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

int n, m;
int valid[105][105];
int cnt[105];
int count1[1100];

int dp[105][105][105];

void cal_count1() {
  for (int i = 0; i < 1 << m; ++i) {
    // gcc编译器内置函数
    count1[i] = __builtin_popcount(i);
  }
}

void cal_valid(int i, string& s) {
  for (int j = 0; j < 1 << m; ++j) {
    bool flag = true;
    for (int k = 0, pre = -3; k < m; ++k) {
      if (j & 1 << k) {
        if (s[k] == 'P' && k - pre > 2) {
          pre = k;
        } else {
          flag = false;
          break;
        }
      }
    }
    if (flag)
      valid[i][cnt[i]++] = j;
  }
}

int solve() {
  memset(dp, 0xcf, sizeof dp); 
  dp[0][0][0] = 0; cnt[0] = 1; 
  for (int i = 0; i < cnt[1]; ++i) {
    dp[1][i][0] = count1[valid[1][i]]; 
  }
  for (int i = 2; i <= n; ++i) {
    // i行
    for (int j = 0; j < cnt[i]; ++j) {
      // i-1行
      for (int k = 0; k < cnt[i - 1]; ++k) {
        // i-2行
        for (int l = 0; l < cnt[i - 2]; ++l) {
          if (valid[i][j] & valid[i - 1][k] || valid[i][j] & valid[i - 2][l] || valid[i - 1][k] & valid[i - 2][l]) continue;
          dp[i][j][k] = std::max(dp[i][j][k], dp[i - 1][k][l] + count1[valid[i][j]]); 
        }
        // dp[i][j][k] +=  
      }
    }
  }
  return *std::max_element(&dp[n][0][0], &dp[n][105][105]);
}

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    string s;
    cin >> s; 
    cal_valid(i, s); 
  }
  cal_count1(); 

  cout << solve() << endl; 

  return 0;
}