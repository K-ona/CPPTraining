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

constexpr int maxn = 1e5 + 5; 
int a[maxn]; 

int main()
{
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */
 
    int n, t; 
    for (cin >> t; t-- && cin >> n; ) {
        map <int, int> cnt; 
        rep (i, 0, n) {
            cin >> a[i]; 
            // --a[i]; 
            ++cnt[a[i]]; 
        }
        auto sorted = cnt; sorted.clear();  
        for (auto x: cnt) {
            sorted[x.second]++; 
        }

        int pos = 0; 
        int Max = sorted.rbegin()->first; 
        // cout << sorted.end()
        // cout << "Max == " << Max << endl; 
        vector<int> box(Max); 
        for (auto x = sorted.crbegin(); x != sorted.crend(); x++) {
            if (x->first == 1) break; 
            int tmpc = x->second * x->first; 
            // cout << "tmpc == " << tmpc << endl; 
            for (int i = 0; i < tmpc; i++) {
                ++box[(pos + i) % Max]; 
            }
            pos = (pos + tmpc) % Max; 
        }
        // cout << *(min_element(box.begin(), box.end() - 1)) << " " << sorted[1] << endl; 

        if (pos == Max - 1) pos = 0; 
        for (int i = 0; i < sorted[1]; i++)
        {
            ++box[(pos + i) % (Max - 1)]; 
        }
        int ans = *(min_element(box.begin(), box.end() - 1)); 
        cout << ans - 1 << endl; 
        // cout << *(min_element(box.begin(), box.end())) + cnt[1] / (Max - 1) << endl; 
    }
    return 0;
}