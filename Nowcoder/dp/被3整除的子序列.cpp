#include <iostream>

int dp[55][10]; 
static int mod = 1e9 + 7;

int main() {
    std::string s; 
    std::cin >> s;
    dp[0][(s[0] - '0') % 3] = 1; 
    for (int i = 1; i < s.size(); ++i) {
        dp[i][(s[i] - '0') % 3] = 1; 
        for (int j = 0; j < i; ++j) {
            for (int k = 0; k < 3; ++k)
                dp[i][(s[i] - '0' + k) % 3] += dp[j][k], dp[i][(s[i] - '0' + k) % 3] %= mod; 
        }
    }
    long long res = 0; 
    for (int i = 0; i < s.size(); ++i) {
//         std::cout << dp[i][0] << std::endl;
        res += dp[i][0]; 
        res %= mod;
    }
    std::cout << res << std::endl; 
    return 0;
}