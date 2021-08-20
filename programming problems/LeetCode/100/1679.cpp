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
public:
    int maxOperations(vector<int>& nums, int k) {
        int n = nums.size(); 
        int ans = 0; 

        unordered_map<int, int> M; 
        for (auto x: nums)
        {
            M[x]++; 
        }

        sort(nums.begin(), nums.end()); 
        n = unique(nums.begin(), nums.end()) - nums.begin(); 

        for (int i = n - 1; ~i; i--)
        {
            if (nums[i] < k)
            {
                int p = lower_bound(nums.begin(), nums.begin() + i, k - nums[i]) - nums.begin(); 
                if (p < i && nums[p] + nums[i] == k) ans += min(M[nums[i]], M[nums[p]]); 
                if (nums[i] * 2 == k) ans += M[nums[i]] / 2; 
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