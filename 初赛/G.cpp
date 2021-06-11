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
const ll mod = 998244353;
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
    string s; 
    map<char, int> cnt; 
    cin >> n >> s; 

    bool flag = true; 
    for (auto c: s) {
        cnt[c]++; 
        if (cnt[c] > 1) {
            flag = false; 
        }
    }
    if (flag) {
        cout << powmod(62 - s.size(), n) << endl; 
        return 0; 
    }
    if (n == s.size()) {
        cout << (powmod(62, n) - 1 + mod) % mod << endl; 
    }
    else if (s.size() < n) {
        cout << (powmod(62, n) - (n - s.size() + 1) * powmod(62, n - s.size())) % mod << endl; 
    }
    else {
        cout << powmod(62, n) << endl; 
    }
    return 0;
}