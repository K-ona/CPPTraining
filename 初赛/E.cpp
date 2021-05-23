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

struct E
{
    int s, t; 
    bool operator<(E other) {
        if (t != other.t) return t < other.t; 
        return s > other.s; 
    }
}node[200005];

map<int, int> Map; 

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
    rep(i, 0, n) {
        cin >> node[i].s >> node[i].t;
    }
    sort(node, node + n);
    int ans = 0; 
    int cur = 0; 
    for (int i = 0; i < n; i++) {
        // cout << node[i].s << node[i].t << endl; 
        // int tmp = max(cur, node[i].s); 
        int tmp = node[i].s;  
        while (tmp <= node[i].t && Map[tmp++] != 0); 
        if (Map[tmp - 1] == 0) {
            Map[tmp - 1]++; 
            cur = tmp - 1; 
            ans++; 
        }
    }
    cout << ans << endl; 

    return 0;
}