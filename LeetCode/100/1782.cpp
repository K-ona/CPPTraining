//created by Kona @VSCode
#include<bits/stdc++.h>

using namespace std;

// #define LOCAL_TEST
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
    vector<int> countPairs(int n, vector<vector<int>> edges, vector<int> queries) {
        vector<int> d(n + 1, 0); 
        vector<int> ans; 
        map<pair<int, int>, int> M; 
        for (auto &x: edges) {
            if (x[0] > x[1]) swap(x[0], x[1]); 
            M[{x[0], x[1]}]++; 
            d[x[0]]++; 
            d[x[1]]++; 
        }

        vector<int> sorted = d; 
        sort(sorted.begin(), sorted.end()); 

        for (auto q: queries) {
            int cnt = 0; 
            for (int i = 1; i <= n; i++) {
                int j = upper_bound(sorted.begin() + i + 1, sorted.end(), q - sorted[i]) - sorted.begin(); 
                cnt += n - j + 1; 
            }

            for (auto x: M) {
                // cout << x.first.first << " " << x.first.second << " " << d[x.first.first] + d[x.first.second] - x.second << endl;
                if (x.first.first != x.first.second  && d[x.first.first] + d[x.first.second] > q && d[x.first.first] + d[x.first.second] - x.second <= q) {
                    cnt--; 
                }
            }
            ans.push_back(cnt); 
        }
        // d.~vector(); 
        return ans; 
    }
};

int main() {
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */

    Solution app; 
    vector<vector<int>> edges{{1,2},{2,4},{1,3},{2,3},{2,1}}; 
    vector<int> quer{2,3}; 
    app.countPairs(4, edges, quer); 
    return 0;
}