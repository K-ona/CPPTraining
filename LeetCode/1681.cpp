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

class Solution
{
    int bound = 1 << 16;
    bool vis[16]; 
    int ans; 
public:
    int minimumIncompatibility(vector<int> &nums, int k)
    {
        int n = nums.size(); 
        memset(vis, 0, sizeof vis); 
        ans = INT32_MAX; 
        // DFS(); 
        return -1;
    }

    void DFS(vector<int> &nums, int iset, int &k, int &n)
    {
        int s = n / k; 
        bool v[16]; 
        for (int i = 0; i < n; i++)
        {
            int Min = INT32_MAX; 
            int Max = -Min; 
            memset(v, 0, sizeof v); 
            for (int j = 0; j < 16; j++)
            {
                if (v[nums[j]]) 
                {
                    Min = INT32_MAX; 
                    return ; 
                }
                if (1 << j & i)
                {
                    Min = min(Min, nums[j]); 
                    Max = max(Max, nums[j]); 
                }
            }
            dp[i] = Max - Min; 
        }
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
    return 0;
}