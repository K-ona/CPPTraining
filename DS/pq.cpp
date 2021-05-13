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

int main()
{
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */
    
    int n; 
    while(cin >> n) {
        map<int, int> cnt; 
        rep(i, 0, n) {
            int tmp; cin >> tmp; 
            cnt[tmp]++; 
        }
        ll ans = 0;
        int mod = 0;
        int x = -1, y = -1;  
        for (auto it = cnt.begin(); cnt.size() + mod > 2; ) {
            if (it->first != x && it->first != y) {
                mod++; 
                x = y; y = it->first; 
                // cout << it->first << " "; 
                if (mod % 3 == 0) ans++, mod = 0; 
                it->second--; 
            }
            else break; 
            if (!it->second) it = cnt.erase(it); 
            else it++; 

            if (it == cnt.end()) it = cnt.begin(); 
        }
        cout << ans << endl; 
    }

    return 0;
}