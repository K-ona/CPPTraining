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
int cnt[maxn]; 
// int good[maxn]; 
vector<int> G[maxn]; 
bool vis[maxn]; 
bool res; 

void DFS(int u)
{
    // good[u] - bad[u] == h[u]
    // good[u] + bad[u] == cnt[u]
    // good[u] == (h[u] + cnt[u]) / 2
    vis[u] = true; 
    int tmp = 0; 
    for (int i = 0; i < G[u].size(); i++)
    {
        if (!vis[G[u][i]])
        {
            DFS(G[u][i]); 
            tmp += (h[G[u][i]] + cnt[G[u][i]]) / 2; 
        }
    }
    int curgood = (h[u] + cnt[u]) / 2; 
    // changemoodnum = curgood - tmp; 

    // cout << "u == " << u << endl; 
    // cout << "curgood == " << curgood << " tmp == " << tmp << endl; 

    if (curgood < tmp || curgood * 2 != h[u] + cnt[u] || cnt[u] < curgood)
    {
        res = false; 
    }
}

void travel(int v)
{
    vis[v] = true; 
    for (int i = 0; i < G[v].size(); i++)
    {
        if (!vis[G[v][i]])
        {
            travel(G[v][i]); 
            cnt[v] += cnt[G[v][i]]; 
        }
    }
    cnt[v] += p[v]; 
}

int main()
{
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("D:\\MyCode\\C++_Training\\Codeforces\\Codeforces Round 660\\input.txt", "r", stdin);
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
        
        memset(vis, 0, sizeof vis); 
        memset(cnt, 0, sizeof cnt); 
        travel(1); 

        res = true; 
        memset(vis, 0, sizeof vis); 
        // memset(good, 0, sizeof good); 
        DFS(1); 
        cout << (res ? "YES" : "NO") << endl; 
    }

    return 0;
}