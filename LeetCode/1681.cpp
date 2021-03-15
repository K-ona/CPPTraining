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

// class Solution {
// public:
//     int minimumIncompatibility(vector<int>& nums, int k) {
//         int n = nums.size();
//         vector<int> value(1 << n, -1);
//         bool vis[16]; 
//         for (int sub = 0; sub < (1 << n); ++sub) {
//             // 判断 sub 是否有 n/k 个 1
//             if (__builtin_popcount(sub) == n / k) {
//                 // 使用数组进行计数
//                 memset(vis, 0, sizeof vis); 
//                 int Max = INT32_MIN, Min = INT32_MAX; 
//                 for (int j = 0; j < n; ++j) {
//                     if (sub & (1 << j)) {
//                         if (!vis[nums[j]]){
//                             vis[nums[j]] = true; 
//                             Max = max(Max, nums[j]); 
//                             Min = min(Min, nums[j]); 
//                         }
//                         else{
//                             Max = INT32_MIN; 
//                             break; 
//                         }
//                     }
//                 }
//                 value[sub] = Max == INT32_MIN ? -1 : Max - Min; 
//             }
//         }
        
//         vector<int> f(1 << n, -1);
//         f[0] = 0;
//         for (int mask = 1; mask < (1 << n); ++mask) {
//             // 判断 mask 是否有 n/k 倍数个 1
//             if (__builtin_popcount(mask) % (n / k) == 0) {
//                 // 枚举子集
//                 for (int sub = mask; sub; sub = (sub - 1) & mask) {
//                     if (value[sub] != -1 && f[mask ^ sub] != -1) {
//                         if (f[mask] == -1) {
//                             f[mask] = f[mask ^ sub] + value[sub];
//                         }
//                         else {
//                             f[mask] = min(f[mask], f[mask ^ sub] + value[sub]);
//                         }
//                     }
//                 }
//             }
//         }
            
//         return f[(1 << n) - 1];
//     }
// };

class Solution {
    int sz; 
    int dp[1 << 16][16]; 
public:
    void DFS(vector<int> &nums, int state, int i){
        if (state = 0) return ; 
        if (__builtin_popcount(state) % sz == 0){
            
        }
    }

    int minimumIncompatibility(vector<int>& nums, int k) {
        sz = nums.size() / k; 
        memset(dp, 0, sizeof(dp)); 
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