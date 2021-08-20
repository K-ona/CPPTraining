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

int sum[100005]; 
vector<int> pos[10005]; 
int maximumUniqueSubarray(vector<int>& nums) 
{
    int n = nums.size(); 
    for(int i = 0; i < n; i++)
    {
        pos[nums[i]].push_back(i); 
    }
    sum[0] = nums[0]; 
    for(int i = 1; i < n; i++)
    {
        sum[i] = nums[i] + sum[i - 1]; 
    }

    int l = 0, r = 0; 
    int ans = -1; 
    for(int r = 0; r < n; r++)
    {
        int p = -1; 
        if(pos[nums[r]][0] != r)    
            p = *(lower_bound(pos[nums[r]].begin(), pos[nums[r]].end(), r) - 1); 
        if(l <= p)
        {
            ans = max(ans, sum[r] - sum[l]); 
            l = p; 
        }    
    }
    ans = max(ans, sum[n - 1] - sum[l - 1]); 
    return ans; 
}

int main()
{
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */

    VI nums;
    int n, m;  
    cin >> n; 
    while(n--)
    {
        cin >> m; 
        nums.push_back(m);
    }
    cout << maximumUniqueSubarray(nums) << endl; 
    return 0;
}