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
    int ans1; 
    int ans2;  
    void DFS(vector<int>& toppingCosts, int sum, int i, int &target) {
        if (i == toppingCosts.size()) return; 
        if (sum < target)
            DFS(toppingCosts, sum, i + 1, target); 
        int sum1 = sum + toppingCosts[i]; 
        int sum2 = sum1 + toppingCosts[i]; 
        if (sum2 < target) {
            ans2 = max(ans2, sum2); 
            DFS(toppingCosts, sum2, i + 1, target); 
            DFS(toppingCosts, sum1, i + 1, target); 
        }
        else {
            ans1 = min(ans1, sum2); 
            if (sum1 < target) {
                ans2 = max(ans2, sum1); 
                DFS(toppingCosts, sum1, i + 1, target); 
            }
            else {
                ans1 = min(ans1, sum1); 
            }
        }
    }
    
    int closestCost(vector<int>& baseCosts, vector<int>& toppingCosts, int target) {
        // sort(baseCosts.begin(), baseCosts.end()); 
        // sort(toppingCosts.begin(), toppingCosts.end()); 
        int n = baseCosts.size(); 
        int m = toppingCosts.size(); 
        ans1 = 1e9;
        ans2 = -1e9;  
        for (auto x: baseCosts) {
            if (x < target) ans2 = max(x, ans2); 
            else ans1 = min(ans1, x); 
            DFS(toppingCosts, x, 0, target); 
        }
        // cout << ans1 << ' ' << ans2 << endl;

        return (abs (ans1 - target) < abs (ans2 - target) ? ans1 : ans2); 
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