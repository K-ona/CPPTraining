// created by Kona @VSCode
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

int dp[105]; 
class Solution {
  const int mod = 1000000007; 
 public:
  int numWays(int n) {
    dp[0] = 1; 
    dp[1] = 1; 
    for (int i = 2; i <= n; ++i) {
      dp[i] = (dp[i - 1] + dp[i - 2]) % mod; 
    }
    return dp[n]; 
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  return 0;
}