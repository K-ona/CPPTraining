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

int a[100005]; 
ll sum[100005]; 

int main()
{
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */

    int n, k; 
    while(cin >> n >> k) {
        rep(i, 0, n) {
            cin >> a[i]; 
        }
        sort(a, a + n); 
        vector<int> res; 
        int cnt = k / 2;
        for (int i = 0; i < cnt; i++) {
            res.push_back(a[i]);
            res.push_back(a[n - i - 1]);
        }
        if (k & 1) { res.push_back((a[0] + a[n - 1] / 2)); }
        sort(res.begin(), res.end()); 
        
        // res[0] - res[1] 
        // res[1] - res[2]
        // res[2] - res[3]
        // == res[0] - res[3]

        // res[0] - res[2]
        // res[1] - res[3]
        // == res[0] + res[1] - res[2] - res[3]
        
        // res[0] - res[3]
        // for (auto x: res) {
        //     cout << x << " "; 
        // }
        // cout << endl; 

        memset(sum, 0, sizeof (sum)); 
        sum[0] = res[0]; 
        for (int i = 1; i < k; i++) {
            sum[i] += sum[i - 1] + res[i]; 
        }

        int len = k - 1; 
        ll ans = 0; 
        for (int i = 1; i <= len / 2; i++) {
            // cout << abs(sum[len] - sum[len - i - 1] - sum[i]) << endl;  
            ans += abs(sum[len] - sum[len - i - 1] - sum[i]); 
        }
        ans *= 2; 
        if (len & 1)
            ans += abs(sum[len] - sum[len / 2] - sum[len / 2]); 

        cout << ans << endl; 
    }
    return 0; 
}