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

int DFS(int n, int mask) {
    
    // for (int i = 0)
    return 0; 
}

int main() {
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */
    int n, m; 
    cin >> n >> m; 
    vector<vector<int>> dp(m, vector<int>(n)); 
    vector<vector<int>> M(m, vector<int>(n)); 

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char tmp; 
            cin >> tmp;
            M[i][j] = tmp - '0';  
        }
    }

    if (min(n, m) > 3) {
        cout << -1 << endl; 
        return 0; 
    }
    if (n == 1 || m == 1) {
        cout << 0 << endl; 
        return 0; 
    }

    cout << DFS(0, 0) << endl; 

    return 0;
}