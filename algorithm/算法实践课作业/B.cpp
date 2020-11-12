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

const int maxn = 2e5 + 10; 

int a[maxn]; 

int main()
{
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */

    int n, k; 
    cin >> n >> k; 
    rep(i, 0, n)
    {
        cin >> a[i]; 
    }
    ll sum = 0, ans = 0;
    for(int i = 0, j = 0; i < n && j < n; j++)
    {
        if(a[j] + sum <= k * (j - i + 1))
        {
            sum += a[j]; 
            cout << i << ' ' << j << " " << sum << endl; 
            ans++; 
        }
        else  
        {
            sum -= a[i]; 
            i++; 
            ans += j - i - 1; 
            sum -= a[j]; 
            j--;  
        }
    }
    ll tot = n * n - n * (n - 1) / 2; 
    if(ans == 0) cout << "0/1" << endl; 
    else cout << ans/ gcd(ans, tot) << "/" << tot / gcd(tot, ans) << endl; 
    return 0;
}