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
    int _;
    int m, d, w;  
    for (cin >> _; _&&_--; )
    {
        cin >> m >> d >> w; 
        // x < y <= m
        // x <= d, y <= d
        // (d - 1) * (y - x) == 0 (mod w)
        int d_dcg = gcd(d - 1, w); 
        int d1 = (d - 1) / d_dcg; 
        int w1 = w / d_dcg; 
        // y - x = w1 * {1, 2, 3, ..., m // w1}
        // res = {m - w1 * k}, k = {1, 2, 3, .., m // w1}
        int m_w1 = (min(m, d) - 1) / w1; 
        cout << 1LL * m_w1 * min(m, d) - 1LL * w1 * (1 + m_w1) * m_w1 / 2 << endl; 
    }
    return 0;
}