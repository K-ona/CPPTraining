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

int dp[100][100]; 
int findMaxForm(vector<string>& strs, int m, int n) {
    int L = strs.size(); 
    memset(dp, 0, sizeof(dp)); 
    for(int i = 0; i < L; i++)
    {
        int cnt0 = 0, cnt1 = 0; 
        for(auto c: strs[i])
        {
            if(c == '1') cnt1++; 
            else cnt0++; 
        }
        for(int j = m; j >= cnt0; j--)
        {
            for(int k = n; k >= cnt1; k--)
            {
                if(cnt0 <= j && cnt1 <= k)
                {
                    dp[j][k] = max(dp[j][k], dp[j - cnt0][k - cnt1] + 1); 
                }
            }
        }
    }

    return dp[m][n]; 
}

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