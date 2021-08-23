//created by Kona @VSCode
#include<bits/stdc++.h>

using namespace std;

#define LOCAL_TEST
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

int r[205], g[205], b[205]; 
int dp[205][205][205]; 

int main() {
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */

    int R, G, B; 
    cin >> R >> G >> B; 
    rep (i, 0, R) cin >> r[i]; sort(r, r + R); 
    rep (i, 0, G) cin >> g[i]; sort(g, g + G); 
    rep (i, 0, B) cin >> b[i]; sort(b, b + B); 

    int res = 0; 
    rep(i, 0, R + 1) {
        rep(j, 0, G + 1) {
            rep(k, 0, B + 1) {
                if (j < G && k < B) 
                    dp[i][j + 1][k + 1] = std::max(dp[i][j][k] + g[j] * b[k], dp[i][j + 1][k + 1]);
                if (i < R && k < B)
                    dp[i + 1][j][k + 1] = std::max(dp[i][j][k] + r[i] * b[k], dp[i + 1][j][k + 1]); 
                if (i < R && j < G) 
                    dp[i + 1][j + 1][k] = std::max(dp[i][j][k] + r[i] * g[j], dp[i + 1][j + 1][k]); 
                res = std::max(res, dp[i][j][k]); 
            }
        }
    }
    cout << res << endl; 
    return 0;
}