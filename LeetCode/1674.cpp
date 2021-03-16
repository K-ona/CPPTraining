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
        for (int i = 0; i <= nums.size() / 2; i++)
        {
            cnt[0][nums[i] + nums[n - i]]++; 
            cnt[0][nums[i] + nums[n - i] + 1]--; 
            int Min = min(nums[i], nums[n - i]); 
            int Max = max(nums[i], nums[n - i]); 
            cnt[1][Min + 1]++; 
            cnt[1][Max + limit + 1]--; 
            if (Min + 1 <= nums[i] + nums[n - i] && nums[i] + nums[n - i] <= Max + limit)
            {
                cnt[1][nums[i] + nums[n - i]]--; 
                cnt[1][nums[i] + nums[n - i] + 1]++; 
            }

            if (2 < Min + 1)
            {
                cnt[2][2]++; 
                cnt[2][Min]--; 
                if (2 <= nums[i] + nums[n - i] && nums[i] + nums[n - i] <= Min - 1)
                {
                    cnt[2][nums[i] + nums[n - i]]--; 
                    cnt[2][nums[i] + nums[n - i] + 1]++; 
                }
            }
            if (Max + limit < 2 * limit)
            {
                cnt[2][Max + limit + 1]++; 
                cnt[2][2 * limit + 1]--; 
                if (Max + limit <= nums[i] + nums[n - i] && nums[i] + nums[n - i] <= 2 * limit)
                {
                    cnt[2][nums[i] + nums[n - i]]--; 
                    cnt[2][nums[i] + nums[n - i] + 1]++; 
                }
            }

        }    
        int ans = INT_MAX; 
        int rem = 0; 
        for (int i = 0; i < 2 * limit; i++)
        {
            rem += cnt[0][i] + cnt[1][i] + cnt[2][i]; 
            cout << rem << endl;
            if (rem * 2 == n + 1)
            {
                ans = min(ans, cnt[1][i] + 2 * cnt[2][i]); 
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