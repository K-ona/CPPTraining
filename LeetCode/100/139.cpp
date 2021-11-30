// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <unordered_set>

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

bool dp[305][305]; 
string str[305][305]; 

class Solution {
 public:
  bool wordBreak(string s, vector<string> wordDict) {
    int n = static_cast<int>(s.size()); 
    std::unordered_set<string> S; 
    memset(dp, false, sizeof(dp)); 
    for (auto word: wordDict) {
        S.insert(word); 
    }
    for (int i = 0; i < n; ++i) {
      for (int j = i; j < n; ++j) {
        str[i][j] = string(s, i, j - i + 1); 
      }
    }
    for (int i = 0; i < n; ++i) { if(S.count(str[i][i])) dp[i][i] = true; }
    for (int len = 1; len < n; ++len) {
      for (int l = 0; l + len < n; ++l) {
        for (int sep = l; sep < l + len; ++sep) {
        //   cout << string(s, l, sep + 1) << " " << string(s, sep + 1, l + len + 1) << endl;
        //   cout << dp[sep + 1][l + len] << " " << dp[l][sep] << endl; 
          if (S.count(str[l][l + len])) dp[l][l + len] = true; 
          if (S.count(str[l][sep]) && dp[sep + 1][l + len]) dp[l][l + len] = true; 
          if (S.count(str[sep + 1][l + len + 1]) && dp[l][sep]) dp[l][l + len] = true; 
        }
      }
    }
    // cout << str[5][7] << endl; 
    // cout << dp[0][4] << " " << dp[5][7] << " " << dp[8][12] << endl; 
    return dp[0][n - 1]; 
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  Solution app;
  app.wordBreak("leetcode", vector<string>{"leet","code"}); 
  return 0;
}