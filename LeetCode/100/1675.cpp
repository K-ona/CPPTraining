//created by Kona @VSCode
#include<bits/stdc++.h>

using namespace std;

#define LOCAL_TEST
#define rep(i, a, n) for (int i = a; i<n; i++)
#define per(i, a, n) for (int i = n - 1; i >= a; i--)
#define pb push_back
#define mp make_pair

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
    int minimumDeviation(vector<int> nums) {
        int n = nums.size(); 
        map<int, int> MP; 
        for (auto x: nums) {
            if (x & 1) x *= 2; 
            MP[x]++; 
        }

        int gMax = MP.rbegin()->first; 
        int Min = MP.begin()->first; 
        int ans = gMax - Min; 
        int odd_cnt = 0; 
        while (odd_cnt < n && !MP.empty()) {
            int Max = MP.rbegin()->first; 
            Min = MP.begin()->first; 
            if (Max & 1){
                MP.erase(--MP.end()); 
                // gMax = Max; 
                break; 
            }
            else {
                MP[Max / 2]++; 
                if ((Max / 2) & 1) odd_cnt++; 
                MP.erase(--MP.end()); 
                if (abs(Max / 2 - Min) <= ans) {
                    ans = min(ans, abs(MP.rbegin()->first - MP.begin()->first)); 
                }
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
    cout << app.minimumDeviation({3, 5}) << endl; 
    return 0;
}