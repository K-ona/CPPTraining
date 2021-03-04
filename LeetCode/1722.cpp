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

class Solution {
public:
    bool vis[100005]; 
    vector<int> G[100005]; 
    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        int n = source.size(); 
        int m = allowedSwaps.size(); 
        for (int i = 0; i < m; i++)
        {
            G[allowedSwaps[i][0]].push_back(allowedSwaps[i][1]); 
            G[allowedSwaps[i][1]].push_back(allowedSwaps[i][0]); 
        }
        memset(vis, 0, sizeof vis);
        int cnt = 0; 
        for (int i = 0; i < n; i++)
        {
            map<int, int> M1; 
            map<int, int> M2; 
            if(!vis[i])
            {
                vis[i] = true; 
                M1[source[i]]++; 
                M2[target[i]]++; 
                dfs(i, M1, M2, source, target); 
            }
            
            for (auto it = M1.begin(); it != M1.end(); it++)
            {
                cnt += min(it->second, M2[it->first]); 
            }
        }
        return n - cnt; 
    }

    int dfs(int ind, map<int, int> &M1, map<int, int> &M2, vector<int>& source, vector<int>& target)
    {
        for (int i = 0; i < G[ind].size(); i++)
        {
            if(!vis[G[ind][i]])
            {
                vis[G[ind][i]] = true; 
                M1[source[G[ind][i]]]++; 
                M2[target[G[ind][i]]]++; 
                dfs(G[ind][i], M1, M2, source, target); 
            }
        }
        return 0; 
    }
};

int main()
{
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */
    Solution app; 
    vector<int> source{1, 2, 3, 4}; 
    vector<int> target{1, 3, 2, 4}; 
    vector<vector<int>> allowedSwaps{}; 

    cout << app.minimumHammingDistance(source, target, allowedSwaps) << endl; 
    return 0;
}