// created by Kona @VSCode
// 杨老师的照相排列: https://www.acwing.com/problem/content/273/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
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

int N[10]; 
ll f[31][31][31][31][31]; 

ll Solve(int N[], int k) {
    // std::fill(&f[0][0][0][0][0], &f[30][30][30][30][30], 0); 
    // std::fill(N + k, N + 5, 0); 
    f[0][0][0][0][0] = 1;
    for (int a = 0; a <= N[0]; a++) {
        for (int b = 0; b <= N[1]; b++) {
            for (int c = 0; c <= N[2]; c++) {
                for (int d = 0; d <= N[3]; d++) {
                    for (int e = 0; e <= N[4]; e++) {
                        if (a < N[0]) f[a+1][b][c][d][e] += f[a][b][c][d][e];
                        if (b < N[1] && b < a) f[a][b+1][c][d][e] += f[a][b][c][d][e];
                        if (c < N[2] && c < b) f[a][b][c+1][d][e] += f[a][b][c][d][e];
                        if (d < N[3] && d < c) f[a][b][c][d+1][e] += f[a][b][c][d][e];
                        if (e < N[4] && e < d) f[a][b][c][d][e+1] += f[a][b][c][d][e];
                    }
                }
            }
        }
    }
    return f[N[0]][N[1]][N[2]][N[3]][N[4]]; 
}

int main() {
    std::ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */
    int k; 
    while(cin >> k && k) {
        memset(N, 0, sizeof N); 
        memset(f, 0, sizeof f); 
        for (int i = 0; i < k; ++i) {
            cin >> N[i]; 
        }
        cout << Solve(N, k) << endl; 
    }

    return 0;
}