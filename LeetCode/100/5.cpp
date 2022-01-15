// created by Kona @VSCode
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


bool dp[1005][1005];
class Solution {
 public:
  string longestPalindrome(string s) {
    memset(dp, 0, sizeof(dp)); 
    int as = 0, al = 1;
    for (int i = 0; i < (int)s.size(); ++i) dp[i][i] = true; 
    for (int i = 0; i + 1 < (int)s.size(); ++i) {
      dp[i][i + 1] = s[i] == s[i + 1]; 
      if (dp[i][i + 1]) {
          as = i, al = 2; 
      }
    }  
    for (int len = 2; len < (int)s.size(); ++len) {
      for (int i = 0; len + i < (int)s.size(); ++i) {
        dp[i][i + len] |= dp[i + 1][i + len - 1] and (s[i] == s[i + len]); 
        if (dp[i][i + len]) {
          as = i, al = len + 1; 
        }
      }
    }
    return s.substr(as, al);
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