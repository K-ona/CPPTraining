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

int dp[1005][1005][2]; 
int sum[1005]; 
int stoneGameVII(vector<int>& stones) {
    int n = stones.size(); 
    memset(dp, 0, sizeof(dp)); 
    memset(sum, 0, sizeof(sum)); 

    sum[0] = stones[0]; 
    for (int i = 1; i < n; i++)
    {
        sum[i] = sum[i - 1] + stones[i]; 
    }

    for (int i = 1; i < n; i ++)
    { 
        dp[i - 1][i][0] = max(stones[i - 1], stones[i]); 
        dp[i - 1][i][1] = max(stones[i - 1], stones[i]); 
    }

    for (int l = 3; l < n; l += 2)
    {
        for (int i = 0; i + l < n; i++)
        {
            dp[i][i + l][0] = max(min(dp[i][i + l - 2][0] + stones[i + l - 1], dp[i + 1][i + l - 1][0] + stones[i]), 
                                  min(dp[i + 2][i + l][0] + stones[i + 1], dp[i + 1][i + l - 1][0] + stones[i + l])); 
            if(i + l + 1 < n)
                dp[i + 1][1 + i + l][1] = max(min(dp[1 + i][i + l - 1][1] + stones[i + l], dp[i + 2][i + l][1] + stones[i + 1]), 
                                              min(dp[i + 3][i + l + 1][1] + stones[i + 2], dp[i + 2][i + l][1] + stones[i + l + 1])); 
        }
    }
    if(n % 2 == 0)
        return dp[0][n - 1][0]; 
    else 
        return max(sum[n - 1] - sum[0] - dp[1][n - 1][1], sum[n - 2] - dp[0][n - 2][0]); 
}


int main()
{
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */
    int a[] = {613,103,624,221,261,595,111,635,569,18,917,136,866,270,111,262,927,743,835,364,716,509,801,813,
            749,870,897,169,737,942,358,295,826,633,54,87,680,637,30,386,12,457,820,973,347,813,558,641,414,306,237,282,535,49,510,880,939,829,280,935,487,
            958,553,465,227,146,185,773,717,977,153,650,445,930,998,13,319,210,378,564,648,732,941,19,94,570,697,19,55,506,130,657,725,581,276,794,805,974,441,41,782,224,641}; 
    vector<int> V; 
    for (int i = 0; i < sizeof(a) / sizeof(int); i++)
    {
        V.push_back(a[i]); 
    }
    cout << stoneGameVII(V) << endl; 
    return 0;
}