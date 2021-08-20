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
    int dp[2005][2005]; // dp[i][j] 当前第i组，前面i-1组异或值为j
    int k; 
public:
    int minChanges(vector<int>& nums, int k) {
        map<int, int> cnt[2005]; 
        int sz[2005]; 
        this->k = k; 
        int Max_cnt[2005]; 
        memset(dp, -1, sizeof dp); 
        memset(sz, 0, sizeof sz); 

        for (int i = 0; i < nums.size(); i++) {
            cnt[i % k][nums[i]]++; 
            sz[i % k]++; 
        }

        int res = 0; 
        for (int i = 0; i < k; i++) {
            Max_cnt[i] = 0; 
            for (auto x: cnt[i]) {
                Max_cnt[i] = max(x.second, Max_cnt[i]); 
            }
            res += sz[i] - Max_cnt[i]; 
        }
    
        res += *min_element(Max_cnt, Max_cnt + k); 
        
        cout << res << endl; 
        // res = nums.size() - res; 
        // cout << res << endl; 
        // cout << DFS(nums, 0, 0, cnt) << endl; 
        return min(res, DFS(nums, 0, 0, cnt, sz)); 
    }   
    
    int DFS(vector<int>& nums, int i, int j, map<int, int> cnt[], int sz[]) {
        if (~dp[i][j]) return dp[i][j]; 
        // if (i == nums.size()) return j == 0 ? 0 : 2005; 
        if (i == k) return j == 0 ? 0 : 1e9; 

        int res = INT_MAX; 
        for (auto x: cnt[i]) {
            res = min(res, DFS(nums, i + 1, j ^ x.first, cnt, sz) + sz[i] - x.second);
        }
        return dp[i][j] = res; 
    }
};


int main() {
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */

    return 0;
}