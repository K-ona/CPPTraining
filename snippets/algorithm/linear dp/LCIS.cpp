// created by Kona @VSCode
// 最长上升公共子序列模板题：https://www.acwing.com/problem/content/description/274/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
#include <map>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::map;
using std::vector;
using std::string;
using std::cout;
using std::endl;

// dp[i][j] 表示以在a[0~i]、b[0~j]两个子序列中，以b[j]为结尾的LCIS（不限定a[i]=b[j]）
int dp[3005][3005]; 

int Solve(int n, int m, int a[], int b[]) {
    ::memset(dp, 0, sizeof dp); 
    b[0] = INT32_MIN;
    for (int i = 1; i <= n; ++i) {
        // 记录该状态(i, j)下决策集合的最优值
        int max = 1; 
        for (int j = 1; j <= m; ++j) {
            dp[i][j] = dp[i - 1][j];
            if (b[j] < a[i]) max = std::max(dp[i - 1][j] + 1, max); 
            else if (b[j] == a[i]) dp[i][j] = std::max(dp[i][j], max); 
        }
    }
    return *(std::max_element(&dp[n][1], &dp[n][m] + 1)); 
}

int a[3005], b[3005]; 

int main() {
    std::ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */

    int n; 
    cin >> n; 
    for (int i = 1; i <= n; i++) cin >> a[i]; 
    for (int i = 1; i <= n; i++) cin >> b[i]; 

    cout << Solve(n, n, a, b) << endl; 
    return 0;
}