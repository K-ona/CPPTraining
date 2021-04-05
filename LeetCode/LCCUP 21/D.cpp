//created by Kona @VSCode
#include<bits/stdc++.h>

using namespace std;

// #define LOCAL_TEST
#define rep(i, a, n) for (int i = a; i<n; i++)
#define per(i, a, n) for (int i = n - 1; i >= a; i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int, int> PII;
typedef vector<pair<int, int>> VPII;
typedef map<int, int> MII;
const ll mod = 1000000007;
ll powmod(ll a, ll b) { ll res = 1; a %= mod; for (; b; b >>= 1) { if (b & 1) res = res * a % mod; a = a * a % mod;}return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}

int x[] = {0, 1, 0, -1, 0}; 
int y[] = {1, 0, -1, 0, 0}; 

class Solution {
    bool ans; 
    int n, m; 
    bool vis[105][55][55][2][3]; 
public:
    bool escapeMaze(vector<vector<string>> maze) {
        ans = false; 
        n = maze[0].size(); 
        m = maze[0][0].size(); 
        memset(vis, 0, sizeof vis); 
        DFS(maze, 0, 0, 0, 0, 0); 
        return ans; 
    }

    void DFS(vector<vector<string>>& maze, int curt, int xp, int yp, int tmpkey, int surkey) {
        // cout << xp << " " << yp << endl; 
        if (xp == n - 1 && yp == m - 1) ans = true; 
        if (ans) return ; 
        if (n - 1 - xp + m - 1 - yp > maze.size() - curt) return ; 
        if (curt == maze.size() - 1) return ; 
        if (vis[curt][xp][yp][tmpkey][surkey]) return ; 
        vis[curt][xp][yp][tmpkey][surkey] = true; 
        
        for (int i = 0; i < 5; i++) {
            int x2 = xp + x[i]; 
            int y2 = yp + y[i];
            if (x2 < 0 || x2 >= n || y2 < 0 || y2 >= m) continue; 
            if (maze[curt + 1][x2][y2] == '.') {
                DFS(maze, curt + 1, x2, y2, tmpkey, i == 4 ? surkey : min(1, surkey)); 
            }
            else {
                if (!tmpkey) {
                    DFS(maze, curt + 1, x2, y2, 1, i == 4 ? surkey : min(1, surkey)); 
                }
                if (!surkey || surkey == 2 && i == 4) {
                    DFS(maze, curt + 1, x2, y2, tmpkey, 2); 
                }
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */

    Solution app; 
    cout << app.escapeMaze({{".#.","#.."},{"...",".#."},{".##",".#."},{"..#",".#."}}); 

    return 0;
}