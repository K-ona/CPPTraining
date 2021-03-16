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

int cnt[3][10]; 

class Solution {
public:
    int minMoves(vector<int> nums, int limit) {
        int n = nums.size() - 1; 
        memset(cnt, 0, sizeof cnt); 
        for (int i = 0; i <= n / 2; i++){
            int sum = nums[i] + nums[n - i]; 
            cnt[0][sum]++; 
            cnt[0][sum + 1]--; 

            int Min = min(nums[i], nums[n - i]) + 1; 
            int Max = max(nums[i], nums[n - i]) + limit; 
            cnt[1][Min]++; 
            cnt[1][sum]--; 
            cnt[1][sum + 1]++; 
            cnt[1][Max + 1]--; 

            if (2 < Min){
                cnt[2][2]++; 
                cnt[2][Min]--; 
            }
            if (Max < 2 * limit){
                cnt[2][Max + 1]++; 
                cnt[2][2 * limit + 1]--; 
            }
        }    

        int ans = INT_MAX; 
        vector<int> rem(3, 0);  
        for (int i = 2; i <= 2 * limit; i++){
            rem[0] += cnt[0][i]; 
            rem[1] += cnt[1][i];
            rem[2] += cnt[2][i];

            int sum = (rem[0] + rem[1] + rem[2]) * 2; 
            // cout << sum << endl;
            if (sum >= n + 1){
                ans = min(ans, rem[1] + 2 * rem[2]); 
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
    Solution app; 
    cout << app.minMoves({1,2,4,3}, 4) << endl; 
    return 0;
}