bool vaild[2005][2005]; 
int dp[20005]; 
int len; 
class Solution {
public:
    int minCut(string s) {
        memset(dp, 0x3f, sizeof(dp)); 
        memset(vaild, 0, sizeof(vaild)); 
        len = s.size(); 
        for (int i = 0; i < len; ++i) {
            vaild[i][i] = true; 
        }

        for (int lth = 1; lth < len; ++lth) {
            for (int l = 0; l + lth < len; ++l) {
                vaild[l][l + lth] = ((l + 1 > l + lth - 1) or vaild[l + 1][l + lth - 1]) and s[l] == s[l + lth];  
            }
        }

        dp[0] = 0; 
        for (int i = 0; i < len; ++i) {
            for (int j = 0; j <= i; ++j) {
                if (vaild[j][i]) dp[i] = std::min(dp[i], j ? (dp[j - 1] + 1) : 0);
            }
        }
        return dp[len - 1]; 
    }
};