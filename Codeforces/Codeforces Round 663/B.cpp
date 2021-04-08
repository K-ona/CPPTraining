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

std::string Map[105]; 
bool dir[105][105]; 
int main() {
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */
    int t, n, m; 
    for (cin >> t; t-- && cin >> n >> m; ) {
        for (int i = 0; i < n; i++) {
            cin >> Map[i]; 
            for (int j = 0; j < m; j++) {
                dir[i][j] = Map[i][j] == 'R'; 
            }
        }

        int res = 0; 
        for (int i = 0; i < n; i++) {
            if (dir[i][m - 1]) res++; 
        }
        for (int i = 0; i < m; i++) {
            if (!dir[n - 1][i]) res++; 
        }    
        cout << res - 1 << endl; 
    }
    return 0;
}