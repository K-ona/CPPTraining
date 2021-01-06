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

int dp[105][105][105]; 
int maxHeight(vector<vector<int>>& cuboids) 
{
    int ans = -1; 
    int n = cuboids.size(); 
    for(int i = 0; i < n; i++)
    {
        sort(cuboids[i].begin(), cuboids[i].end()); 
    }

    memset(dp, 0, sizeof(0)); 
    for(int x = 0; x <= 100; x++)
    {
        for(int y = 0; y <= 100; y++)
        {
            if(x <= cuboids[0][0] && y <= cuboids[0][1])
            {
                dp[x][y][0] = max(dp[x][y][0], cuboids[0][2]); 
            }
            if(x <= cuboids[0][1] && y <= cuboids[0][2])
            {
                dp[x][y][0] = max(dp[x][y][0], cuboids[0][0]); 
            }
            if(x <= cuboids[0][0] && y <= cuboids[0][2])
            {
                dp[x][y][0] = max(dp[x][y][0], cuboids[0][1]); 
            }
        }
    }
    
    for(int i = 1; i < n; i++)
    {
        for(int x = 0; x <= 100; x++)
        {
            for(int y = 0; y <= 100; y++)
            {
                if(x >= cuboids[i][0] && y >= cuboids[i][1])
                {
                    dp[cuboids[i][0]][cuboids[i][1]][i] = max(dp[x][y][i - 1] + cuboids[i][2], dp[cuboids[i][0]][cuboids[i][1]][i]); 
                }
                if(x >= cuboids[i][1] && y >= cuboids[i][2])
                {
                    dp[cuboids[i][1]][cuboids[i][2]][i] = max(dp[x][y][i - 1] + cuboids[i][0], dp[cuboids[i][1]][cuboids[i][2]][i]); 
                }
                if(x >= cuboids[i][0] && y >= cuboids[i][2])
                {
                    dp[cuboids[i][0]][cuboids[i][2]][i] = max(dp[x][y][i - 1] + cuboids[i][1], dp[cuboids[i][0]][cuboids[i][2]][i]); 
                }
            }
        }
    }

    for(int i = 0; i <= 100; i++)
    {
        for(int j = 0; j <= 100; j++)
        {
            ans = max(ans, dp[i][j][n - 1]); 
        }
    }
    return ans; 
}

bool cmp(vector<int> A, vector<int> B)
{
    if(A[0] <= B[0] &&)
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