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

const int maxn = 10; 
ll a[maxn], b[maxn]; 
int ind[maxn]; 
int len[maxn]; 
vector<int> G[maxn]; 
ll ans; 
int res[maxn]; 
bool vis[maxn]; 
int ind2[maxn]; 

void travel(int v)
{
    len[v] = 1; 
    for (auto u: G[v])
    {
        travel(u); 
        len[v] = len[u] + 1; 
    }
}

void DFS(int v)
{
    // cout << "v == " << v << endl; 
    // cout << "ind[v] == " << ind[v] << endl; 
    ans += a[v]; 
    vis[v] = true; 
    for (auto u: G[v])
    {
        ind[u]--; 
        res[v] += 1LL * (len[v] - 1) * a[v]; 
        if (res[v] >= 0)
            a[u] += a[v]; 
        else 
        {
            res[u] = 0; 
        }
    }
}

stack<VI> S; 

void output(int u)
{
    cout << u << " ";
    for (auto v: G[u])
    {
        output(v); 
    }
}

int main()
{
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("D:\\Document\\GitHub\\CPP-Training\\Codeforces\\Codeforces Round 660\\input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */

    int n; 
    cin >> n;

    memset(ind, 0, sizeof ind); 
    rep(i, 0, n) cin >> a[i]; 
    rep(i, 0, n) 
    {
        cin >> b[i]; 
        if(~b[i])
        {
            G[i].push_back(b[i] - 1); 
            ind[b[i] - 1]++; 
        }
    }

    rep(i, 0, n) ind2[i] = ind[i]; 
    rep(i, 0, n) travel(i); 
    bool flag = true; 
    while(flag)
    {
        flag = false; 
        rep(i, 0, n)
        {
            if (ind[i] == 0 && vis[i] == false)
            {
                flag = true; 
                DFS(i); 
            }
        }
    }
    
    cout << ans << endl; 
    for (int i = 0; i < n; i++)
    {
        if (ind2[i] == 0)
        {
            output(i); 
        }
    }
    return 0;
}