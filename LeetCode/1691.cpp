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

int G[105][105]; 
int size[105]; 
int height[105]; 
bool vis[105]; 
int res; 

void DFS(int i, vector<vector<int>>& cuboids)
{
    int maxh = 0; 
    vis[i] = true; 
    for(int j = 0; j < size[i]; j++)
    {
        if(vis[G[i][j]] == false)
            DFS(G[i][j], cuboids); 
        maxh = max(maxh, height[G[i][j]]); 
    }
    res = max(res, height[i] = maxh + cuboids[i][2]); 
}

int maxHeight(vector<vector<int>>& cuboids) 
{
    int n = cuboids.size(); 
    memset(size, 0, sizeof size); 
    memset(height, 0, sizeof height); 
    memset(vis, 0, sizeof(vis)); 
    for(int i = 0; i < n; i++)
    {
        sort(cuboids[i].begin(), cuboids[i].end());
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(cuboids[i][0] >= cuboids[j][0] && cuboids[i][1] >= cuboids[j][1] && cuboids[i][2] >= cuboids[j][2]) G[i][size[i]++] = j; 
            if(cuboids[i][0] <= cuboids[j][0] && cuboids[i][1] <= cuboids[j][1] && cuboids[i][2] <= cuboids[j][2]) G[j][size[j]++] = i; 
        }
    }
    res = -1; 
    for(int i = 0; i < n; i++)
    {
        if(vis[i] == false)
        {
            DFS(i, cuboids); 
        }
    }
    return res; 
}

vector<vector<int>> VVI; 

int main()
{
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */
    vector<int> V1{7,11,17};
    VVI.push_back(V1);  
    vector<int> V2{7,11,17};
    VVI.push_back(V2);  
    vector<int> V3{7,11,17};
    VVI.push_back(V3);  
    vector<int> V4{7,11,17};
    VVI.push_back(V4);  
    vector<int> V5{7,11,17};
    VVI.push_back(V5);  
    vector<int> V6{7,11,17};
    VVI.push_back(V6);  
    // vector<int> V3{45, 23, 12};
    // VVI.push_back(V3);  
    // cout << VVI.size() << endl; 
    cout << maxHeight(VVI) << endl;
    return 0;
}