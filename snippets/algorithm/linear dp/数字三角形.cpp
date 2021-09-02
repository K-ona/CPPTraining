// created by Kona @VSCode
// 数字三角形模板题：https://www.acwing.com/problem/content/900/
// 样例大小： 5
// 7
// 3 8
// 8 1 0 
// 2 7 4 4
// 4 5 2 6 5
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::map;
using std::vector;
using std::string;
using std::cout;
using std::endl;

int a[505][505]; 
int dp[505][505]; 

int Solve(int a[][505], int n) {
    std::fill(&dp[0][0], &dp[n - 1][n - 1], INT32_MIN); 
    dp[0][0] = a[0][0]; 
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j <= i; ++j) {
            dp[i + 1][j] = std::max(dp[i + 1][j], dp[i][j] + a[i + 1][j]); 
            dp[i + 1][j + 1] = std::max(dp[i + 1][j + 1], dp[i][j] + a[i + 1][j + 1]); 
        }
    }
    return *std::max_element(&dp[n - 1][0], &dp[n - 1][n]); 
}

int main() {
    std::ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */

    int n; 
    cin >> n; 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; ++j) {
            cin >> a[i][j]; 
        }
    }

    cout << Solve(a, n) << endl; 
    return 0;
}