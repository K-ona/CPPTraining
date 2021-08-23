//created by Kona @VSCode
#include <iostream>
#include <vector>
#include <string>
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

constexpr int maxn = 5e5 + 5; 
int dp[maxn][3]; 

class Solution {
    int n; 
public:
    int minSideJumps(vector<int>& obstacles) {
        n = obstacles.size() - 1; 
        memset(dp, -1, sizeof dp); 
        return DFS(0, 1, obstacles); 
    }
    int DFS(int cur, int lane, vector<int> &obstacles) {
        if (obstacles[cur] == lane + 1) return 1e9; 
        if (cur == n) return 0; 
        if (~dp[cur][lane]) return dp[cur][lane]; 
        int res = INT32_MAX; 
        for (int i = 0; i < 3; i++) {
            if (obstacles[cur] != i + 1) {
                if (i != lane) res = std::min(res, 1 + DFS(cur + 1, i, obstacles)); 
                else res = std::min(res, DFS(cur + 1, i, obstacles)); 
            }
        }
        return dp[cur][lane] = res; 
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