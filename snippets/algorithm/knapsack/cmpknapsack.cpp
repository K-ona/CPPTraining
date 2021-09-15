// created by Kona @VSCode
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

constexpr int mod = 2147483648; 

ll dp[4005]; 
int solve(int n) {
  memset(dp, 0, sizeof dp); 
  dp[0] = 1; 
  for (int i = 1; i < n; ++i) {
    for (int j = i; j <= n; ++j) {
      dp[j] = (dp[j] + dp[j - i] ) % mod; 
    }
  }
  return dp[n]; 
}

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  int n; 
  cin >> n; 
  cout << solve(n) << endl; 

  return 0;
}