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

vector<int> G[105]; 
int height[105]; 

void DFS(int i, vector<vector<int>>& cuboids)
{
    for(auto j: G[i])
    {
        DFS(j, cuboids); 
        height[i] = max(height[i], height[j] + cuboids[j][2]); 
    }
}

pair<int, int> cmp(vector<int> A, vector<int> B)
{
    pair<int, int> res; res.first = -1; res.second = -1; 
    if(A[0] >= B[0] && A[1] >= B[1] && A[2] >= B[2]) res.first = 1; 
    if(A[0] <= B[0] && A[1] <= B[1] && A[2] <= B[2]) res.second = 1; 
    return res; 
}

int maxHeight(vector<vector<int>>& cuboids) 
{
    int n = cuboids.size(); 
    int ind[105]; 

    memset(height, 0, sizeof height); 
    memset(ind, 0, sizeof ind); 
    for(int i = 0; i < n; i++)
    {
        sort(cuboids[i].begin(), cuboids[i].end());
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            auto tmp = cmp(cuboids[i], cuboids[j]); 
            if(tmp.first == 1) G[i].push_back(j), ind[j]++; 
            if(tmp.second == 1) G[j].push_back(i), ind[i]++; 
        }
    }
    
    for(int i = 0; i < n; i++)
    {
        if(ind[i] == 0)
        {
            DFS(i, cuboids); 
        }
    }
    int res = -1; 
    for(int i = 0; i < n; i++)
    {
        res = max(res, height[i]);    
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
    int n, x, y, z;
    cin >> n; 
    rep(i, 0, n)
    {
        cin >> x >> y >> z; 
        vector<int> V; 
        V.push_back(x);
        V.push_back(y);
        V.push_back(z);
        VVI.push_back(V); 
    }
    cout << VVI.size() << endl; 
    cout << maxHeight(VVI) << endl;
    return 0;
}