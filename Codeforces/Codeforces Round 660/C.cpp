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

const int maxn = 1e5 + 50; 
int p[maxn]; 
int h[maxn]; 
vector<int> G[maxn]; 
bool vis[maxn]; 
bool res; 

pair<int, int> DFS(int u)
{
    // good[u] - bad[u] == h[u]
    // good[u] + bad[u] == p[u]
    // good[u] == (h[u] + p[u]) // 2
    vis[u] = true; 
    int Min = 0; 
    int Sum = 0; 
    bool flag = false; 
    for(auto v: G[u])
    {
        if(!vis[v])
        {
            flag = true; 
            auto tmp = DFS(v); 
            Min += tmp.first; 
            Sum += tmp.second; 
        }
    }
    if(!flag)   return {(p[u] + h[u]) / 2, p[u]}; 
    if(h[u] + Sum > 2 * Min) 
    {   
        res = false; 
        cout << u << ' ' << p[u] << ' ' << h[u] << endl; 
        return {0, 0};
    }
    return {(h[u] + Sum) / 2, Sum}; 
}

int main()
{
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */
    int n, m, t; 
    for(cin >> t; t--; )
    {
        cin >> n >> m; 
        rep(i, 0, n) G[i + 1].clear(); 
        rep(i, 1, 1 + n) cin >> p[i]; 
        rep(i, 1, 1 + n) cin >> h[i]; 
        int u, v; 
        rep(i, 1, n) cin >> u >> v, G[u].push_back(v), G[v].push_back(u);
        
        res = true; 
        memset(vis, 0, sizeof vis); 
        DFS(1); 
        cout << (res ? "YES" : "NO") << endl; 
    }

    return 0;
}