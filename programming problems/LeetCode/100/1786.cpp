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

struct 
{
    int to; 
    int next; 
    int w; 
}edge[8 * 1005];
int head[20005], ecnt; 
bool vis[20005];  

void init() {
    memset(head, -1, sizeof head); 
    memset(vis, 0, sizeof vis); 
    ecnt = 0; 
}

void add_edge(int u, int v, int w) {
    edge[ecnt].to = v; 
    edge[ecnt].w = w; 
    edge[ecnt].next = head[u]; 
    head[u] = ecnt++; 
}


struct node
{
    int w; 
    int v; 
    bool operator<(const node &A) const {
        return w > A.w; 
    }
};

void Dijkstra(int source, int GS, vector<int> &Dis) {
    priority_queue<node> PQ; 
    // vector<int> Dis(GS + 1, INT_MAX); 
    Dis[source] = 0; 
    PQ.push({0, source}); 

    while (!PQ.empty())
    {
        auto cur = PQ.top(); PQ.pop(); 
        int u = cur.v; 
        if (vis[u]) continue; 
        vis[u] = true; 

        for (int i = head[u]; ~i; i = edge[i].next) {
            if (Dis[edge[i].to] > Dis[u] + edge[i].w) {
                Dis[edge[i].to] = Dis[u] + edge[i].w; 
                PQ.push({Dis[edge[i].to], edge[i].to}); 
            }
        }
    }
    return ;
}

class Solution {
    vector<int> dis; 
    vector<int> dp; 
    int n; 
public:
    int countRestrictedPaths(int n, vector<vector<int>>& edges) {
        init(); 
        for (auto x: edges) {
            add_edge(x[0], x[1], x[2]); 
            add_edge(x[1], x[0], x[2]); 
        }
        
        Dijkstra(n, n, this->dis); 
        this->n = n; 
        return DFS(1); 
    }

    Solution (): dis(20005, INT_MAX), n(0), dp(20005, -1) {} 

    ll DFS(int u) {
        if (u == n) return 1; 
        if (~dp[u]) return dp[u]; 
        ll res = 0; 
        for (int i = head[u]; ~i; i = edge[i].next) {
            if (dis[edge[i].to] < dis[u]) {
                res += DFS(edge[i].to); 
                res %= mod; 
            }
        }
        return dp[u] = res; 
    }
};

int main() {
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */
    vector<vector<int>> edges = {{1,3,1},{4,1,2},{7,3,4},{2,5,3},{5,6,1},{6,7,2},{7,5,3},{2,6,4}}; 

    Solution app; 
    app.countRestrictedPaths(7, edges); 
    return 0;
}