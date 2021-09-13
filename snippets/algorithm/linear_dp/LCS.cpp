// created by Kona @VSCode
// 最长公共子序列模板题: https://www.acwing.com/problem/content/899/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cstring>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::map;
using std::vector;
using std::string;
using std::cout;
using std::endl;

int a[1005], b[1005]; 
int dp[1005][1005]; 

int Solve(string &a, int N, string &b, int M) {
    memset(dp, 0, sizeof dp); 
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (i > 0 && j > 0)
                dp[i][j] = std::max(dp[i][j - 1], dp[i - 1][j]); 
            if (a[i] == b[j]) 
                dp[i][j] = std::max(dp[i][j], dp[i - 1][j - 1] + 1); 
        }
    }
    return dp[N - 1][M - 1]; 
}

int main() {
    std::ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */

    int N, M; 
    cin >> N >> M; 
    string a, b; 
    cin >> a >> b; 

    cout << Solve(a, N, b, M) << endl; 
    return 0;
}