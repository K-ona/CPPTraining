#include <string.h>
#include <iostream>

bool dp[105][105];
class Solution {
 public:
  bool isInterleave(std::string s1, std::string s2, std::string s3) {
    memset(dp, 0, sizeof(dp));
    int len1 = s1.size(), len2 = s2.size(); 
    if (len1 + len2 != s3.size()) 
      return false;
    if (s1 == s3 or s2 == s3)
      return true;

    for (int i = 0; i <= len1; ++i) {
      for (int j = 0; j <= len2; ++j) {
        if (!i and !j) {
          dp[i][j] = true; 
          continue;
        }
        if (i == 0) {
          dp[i][j] = dp[i][j - 1] and s2[j - 1] == s3[i + j - 1]; 
          // s2.substr(0, j) == s3.substr(0, i + j);
          continue;
        }
        if (j == 0) {
          dp[i][j] = dp[i - 1][j] and s1[i - 1] == s3[i + j - 1]; 
          // s1.substr(0, i) == s3.substr(0, i + j);
          continue;
        }

        dp[i][j] = (dp[i][j - 1] and s3[i + j - 1] == s2[j - 1]) or
                   (dp[i - 1][j] and s3[i + j - 1] == s1[i - 1]);
      }
    }
    return dp[len1][len2];
  }
};