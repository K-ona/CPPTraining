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

    memset(dp, 0, sizeof(0)); 
    
    for(int i = 0; i < n; i++)
    {
        for(int x = 100; x >= 0; x--)
        {
            for(int y = 100; y >= 0; y--)
            {
                for(int z = 100; z >= 0; z--)
                {
                    if(x >= cuboids[i][0] && y >= cuboids[i][1] && z >= cuboids[i][2])
                    {
                        dp[x][y][z] = max(dp[x][y][z], dp[x - cuboids[i][0]][y - cuboids[i][1]][z - cuboids[i][2]] + cuboids[i][2]); 
                    }
                    if(x >= cuboids[i][1] && y >= cuboids[i][2] && z >= cuboids[i][0])
                    {
                        dp[x][y][z] = max(dp[x][y][z], dp[x - cuboids[i][1]][y - cuboids[i][2]][z - cuboids[i][0]] + cuboids[i][0]); 
                    }
                    if(x >= cuboids[i][0] && y >= cuboids[i][2] && z >= cuboids[i][1])
                    {
                        dp[x][y][z] = max(dp[x][y][z], dp[x - cuboids[i][0]][y - cuboids[i][2]][z - cuboids[i][1]] + cuboids[i][1]); 
                    }
                }
            }
        }
    }

    return dp[100][100][100]; 
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