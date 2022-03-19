// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <set>

#include <string.h>

// #define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::queue;
using std::string;
using std::vector;

bool dp[2005][2005]; 
class Solution {
 public:
  bool isMatch(string s, string p) {
    memset(dp, 0, sizeof dp); 
    s = "0" + s; 
    p = "0" + p; 
    dp[0][0] = true; 
    int n = s.size(); 
    int m = p.size(); 
    for (int i = 1; i < m and p[i] == '*'; ++i) dp[0][i] = true; 
    
    int pre[2] = {0, 2005}; 
    for (int j = 1; j < m; ++j) {
      for (int i = 1; i < n; ++i) {
        if (p[j] == '?') {
          dp[i][j] = dp[i - 1][j - 1]; 
        }
        else if (p[j] == '*') {
          dp[i][j] = true; 
          if (pre[~j & 1] > i) {
            dp[i][j] = false; 
          } 
        } else {
          dp[i][j] = dp[i - 1][j - 1] and (s[i] == p[j]);
        }
        if (pre[j & 1] == 2005 and dp[i][j]) pre[j & 1] = i; 
      }
      pre[~j & 1] = 2005;
    }
    return dp[n - 1][m - 1]; 
  }
};



int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  Solution().isMatch("aab", "c*a*b"); 
  return 0; 
}