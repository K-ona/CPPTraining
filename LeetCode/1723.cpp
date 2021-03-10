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
    int dp[13][1 << 12]; 
    int time[1 << 12]; 
public:
    int minimumTimeRequired(vector<int>& jobs, int k) {
        // sort(jobs.begin(), jobs.end()); 
        int n = jobs.size(); 
        int res = 0; 
        int MaxJ = 1 << n; 

        memset(time, 0, sizeof time); 
        for (int i = 0; i < MaxJ; i++)
        {
            for (int j = 0; j < n; j++)
            {
                time[i] += (i & (1 << j)) == 0 ? 0 : jobs[j]; 
            }
        }

        memset(dp, 0x7f, sizeof dp); 
        for (int i = 0; i < MaxJ; i++)
        {
            dp[0][i] = time[i]; 
        }

        for (int i = 1; i < k; i++)
        {
            for(int j = 1; j < MaxJ; j++)
            {
                for(int k = 1; k < MaxJ; k++)
                {
                    if(k & j == 0)
                    {
                        dp[i][k | j] = min(dp[i][k | j] , max(dp[i - 1][j], time[k])); 
                    }
                }
            }
        }
        
        return dp[k - 1][MaxJ - 1]; 
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
    VI p1{3, 2, 3}; 
    int p2 = 3;
    cout << app.minimumTimeRequired(p1, p2) << endl; 
    return 0;
}