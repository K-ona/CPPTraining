// created by Kona @VSCode
// 状压dp例题：https://www.acwing.com/problem/content/description/294/

// 状压dp常见做法有两种
// 1. 枚举+合法性判断
// 2. 生成: 生成合法的状态，常用于比较繁琐、复杂的状态转移

// 本例选择第2种做法
// 用0,1,2表示每个点的状态，2表示炮兵位置
// 2下面必须为1, 1下面必须为0
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

int n, m; 
string M[105]; 
int pow3[105]; 

int dp[105][60000]; 

void DFS(int row, int col, int state, int new_state, int pre2, int cnt) {
  if (col == m) {
    dp[row][new_state] = std::max(dp[row][new_state], dp[row - 1][state] + cnt); 
    return; 
  }
  // 2下面放1
  if (state / pow3[col] % 3 == 2) {
    DFS(row, col + 1, state, new_state + 1 * pow3[col], pre2, cnt); 
    return; 
  }
  // 1下面放0
  if (state / pow3[col] % 3 == 1) {
    DFS(row, col + 1, state, new_state, pre2, cnt); 
    return; 
  }
  // 0下面放2
  if (col - pre2 > 2 && M[row][col] == 'P')
    DFS(row, col + 1, state, new_state + 2 * pow3[col], col, cnt + 1);   
  // 0下面放0
  DFS(row, col + 1, state, new_state, pre2, cnt);   
}

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  cin >> n >> m; 
  for (int i = 1; i <= n; ++i) cin >> M[i]; 

  pow3[0] = 1; 
  for (int i = 1; i <= m; ++i) pow3[i] = pow3[i - 1] * 3; 

  memset(dp, 0xcf, sizeof(dp)); 
  dp[0][0] = 0; 
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < pow3[m]; ++j) {
      if (dp[i - 1][j] != 0xcfcfcfcf) {
        DFS(i, 0, j, 0, -3, 0); 
      }
    }
  }

  cout << *std::max_element(&dp[n][0], &dp[n][pow3[m]]) << endl; 
  return 0;
}