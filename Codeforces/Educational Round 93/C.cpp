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
string a; 
ll p[maxn]; 

int main() {
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */

    int _, n;
    for (cin >> _; _-- && cin >> n >> a; ) {
        unordered_map<ll, int> UMap; 
        UMap[0] = 1; 
        ll ans = 0; 
        rep(i, 0, n) {
            p[i + 1] = p[i] + a[i] - '0'; 
            ++UMap[p[i + 1] - i - 1]; 
            ans += UMap[p[i + 1] - i - 1] - 1; 
        }
        cout << ans << endl; 
    }

    return 0;
}