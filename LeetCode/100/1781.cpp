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
    int beautySum(string s) {
        int ans = 0; 
        for (int len = 3; len <= s.size(); len++) {
            vector<int> map(26); 
            for (int i = 0; i < len; i++) map[s[i] - 'a']++; 

            auto Max = *max_element(map.begin(), map.end()); 
            int Min = INT_MAX; 
            for (auto x: map) {
                if (x && x < Min) Min = x; 
            }
            ans += Max - Min; 

            for (int i = 1; i + len <= s.size(); i++) {
                map[s[i + len - 1] - 'a']++; 
                map[s[i - 1] - 'a']--; 
                auto Max = *max_element(map.begin(), map.end()); 
                int Min = INT_MAX; 
                for (auto x: map) {
                    if (x && x < Min) Min = x; 
                }
                ans += Max - Min; 
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