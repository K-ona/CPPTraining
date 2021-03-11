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
    bool dp[2005][2005]; 
public:
    bool checkPartitioning(string s) {
        int n = s.size(); 
        memset(dp, 0, sizeof(dp)); 

        for(int i = 0; i < n - 1; i++)
            dp[i][i] = true, dp[i][i + 1] = s[i] == s[i + 1];
        dp[n - 1][n - 1] = true; 

        for (int l = 2; l < n; l++)
        {
            for (int i = 0; i + l < n; i++)
            {
                dp[i][i + l] = (s[i] == s[i + l] && dp[i + 1][i + l - 1]); 
            }
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 1; j + i < n - 1; j++)
            {
                if (dp[0][i] && dp[i + 1][i + j] && dp[i + j + 1][n - 1])
                {
                    return true;
                } 
            }
        }
        return false; 
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
    app.checkPartitioning("bcbddxy"); 
    return 0;
}