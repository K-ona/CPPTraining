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
        long long sum[(int)1e5 + 5]; 
public:
    vector<bool> canEat(vector<int>& candiesCount, vector<vector<int>>& queries) {
        int m = queries.size(); 
        int n = candiesCount.size(); 

        sum[0] = candiesCount[0]; 
        for (int i = 1; i < n; i++)
            sum[i] = sum[i - 1] + candiesCount[i]; 
        
        vector<bool> ans; 
        for (int i = 0; i < m; i++)
        {
            long long min = (queries[i][0] > 0 ? sum[queries[i][0] - 1] : 0) / queries[i][2]; 
            if (min * queries[i][2] == sum[queries[i][0]])
                min++;
            long long max = sum[queries[i][0]] - 1; 
            if (min <= queries[i][1] && max >= queries[i][1])
            {
                ans.push_back(true);
            }
            else 
            {
                ans.push_back(false); 
            }
        }
        return ans; 
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