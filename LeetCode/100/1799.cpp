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
int gcd(int a, int b) { return b ? gcd(b, a % b) : a;}

int dp[8][1024 * 16]; 
class Solution {
    int n; 
public:
    int maxScore(vector<int>& nums) {
        memset(dp, -1, sizeof dp); 
        n = nums.size(); 
        int16_t x = 0;
        for (int i = 0; i < n; i++) {
            x <<= 1; x |= 1;
        }
        return DFS(x, 1, 0, nums); 
    }

    int DFS(int16_t state, int order, int res, vector<int>& nums) {
        if (state == 0) return 0; 
        if (~dp[order][state]) return dp[order][state]; 
        int Max = INT_MIN;
        for (int i = 0; i < n; ++i) {
            for (int j = 1 + i; j < n; ++j) {
                if ((state & (1 << i)) && (state & (1 << j))) {
                    // cout << "order == " << order << " " << nums[i] << " " << nums[j] << endl; 
                    int tmp = order * gcd(nums[i], nums[j]);
                    Max = max(Max, tmp + DFS(state & (~(1 << i)) & (~(1 << j)), order + 1, res + tmp, nums)); 
                }
            }
        }
        return dp[order][state] = Max; 
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