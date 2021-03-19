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

int main()
{
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */ 
    int n; 
    cin >> n;
    vector<int> A(n); 
    map<int, int> M;
    int a;  
    rep(i, 0, n) cin >> a, M[a]++;
    int cnt4 = 0; 
    int cnt2 = 0;

    for (auto x: M)
    {
        if (x.second >= 4) cnt4 += x.second / 4; 
        if (x.second >= 2) cnt2 += x.second / 2; 
    }

    int q; cin >> q; 
    char c; int x; 
    rep(i, 0, q)
    {
        cin >> c >> x;  
        if (c == '+')
        {
            M[x]++; 
            if (M[x] % 4 == 0) cnt4++; 
            if (M[x] % 2 == 0) cnt2++; 
        }
        else 
        {
            M[x]--; 
            if (M[x] % 4 == 3) cnt4--; 
            if (M[x] % 2 == 1) cnt2--; 
        }
        // cout << cnt2 << " " << cnt4 << endl; 
        if (cnt4 && (cnt2 - cnt4 * 2 > 1 || cnt4 > 1) )
            cout << "YES" << endl; 
        else cout << "NO" << endl; 
    }
    return 0;
}