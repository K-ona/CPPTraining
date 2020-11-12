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

const int maxn = 1e6 + 50; 
bool visit[maxn]; 
int head[maxn]; 
int cnt; 

struct P
{
    int to;
    int next;
}edge[maxn];

void add_edge(int x, int y)
{
    edge[cnt].to = y;
    edge[cnt].next = head[x];
    head[x] = cnt++;
}

void DFS(int x)
{
    for(int i = head[x]; ~i; i = edge[i].next)
    {
        int y = edge[i].to; 
        if(!visit[y])
        {
            visit[y] = true; 
            DFS(y); 
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); 
    std::cin.tie(0);
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */

    memset(head, -1, sizeof(head)); 

    int _, n, ans = 0; 
    cin >> n;
    rep(i, 0, n)
    {
        cin >> _; 
        add_edge(i + 1, _); 
        add_edge(_, i + 1); 
    }
    
    for(int i = 1; i <= n; i++)
    {
        if(!visit[i])
        {
            visit[i] = true; 
            DFS(i); 
            ans++; 
        }
    }
    cout << ans << endl; 
    return 0;
}