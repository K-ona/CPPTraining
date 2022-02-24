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

bool dp[22][32]; 
class Solution {
public:
  bool isMatch(string &s, string &p) {
    s = "-" + s; 
    p = "-" + p; 
    int slen = s.size(); 
    int plen = p.size(); 
    memset(dp, 0, sizeof(dp)); 
    dp[0][0] = true; 
    for (int i = 2; i < plen; i += 2) {
      if (p[i] == '*') {
        dp[0][i] = true;
      } else { 
        break;
      }
    }

    for (int j = 1; j < plen; ++j) {
      for (int i = 1; i < slen; ++i) {
        if (s[i] == p[j] or p[j] == '.') { // 单字符直接匹配
          dp[i][j] = dp[i - 1][j - 1]; 
        } else if (p[j] == '*') {
          if (p[j - 1] == '.') {
            for (int k = 0; k < i; ++k) {
              dp[i][j] or_eq dp[k][j]; // .*匹配长度大于0
            }
            dp[i][j] or_eq dp[i][j - 2]; // .*匹配长度等于0
          } else {
              int k = i; 
              while (s[k] == p[j - 1] and !dp[k][j]) { 
                --k; 
              }
              dp[i][j] or_eq dp[i][j - 2];  // x*匹配长度为0
              dp[i][j] or_eq dp[k][j]; // x*匹配长度大于0
          }
        } else {
          dp[i][j] = false; // 不匹配
        }
      }
    }
    return dp[slen - 1][plen - 1]; 
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  // string s = "mississippi"; 
  // string p = "mis*is*ip*."; 

  // string s = "aab"; 
  // string p = "c*a*b"; 

  string s = "aaa"; 
  string p = "ab*a*c*a"; 

  Solution().isMatch(s, p);
  return 0;
}

    // for (int i = 0; i < slen; ++i) {
    //     for (int j = 0; j < plen; ++j) {
    //         cout << "dp[" << i << "][" << j << "] = " << std::boolalpha << dp[i][j] << " "; 
    //     }
    //     cout << endl; 
    // }