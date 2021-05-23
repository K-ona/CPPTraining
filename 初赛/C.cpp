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

int prime[100005]; 
bool flag[1000005]; 
int cnt; 

void cal(){
    for (int i = 2; i < 1000005; i++) {
        // cout << i << endl; 
        if (flag[i] == false) {
            prime[cnt++] = i; 
        }
        for (int j = i; j < 1000005; j += i) {
            // cout << j << endl; 
            flag[j] = true; 
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */

    cal(); 
    // cout << cnt << endl; 
    for (int _, n; cin >> _; ) {
        while (_--){
            cin >> n; 
            // cout << n << endl; 
            int ptr = upper_bound(prime, prime + cnt, n) - prime; 
            // cout << "ptr == " << ptr << endl; 
            cout << 1LL * prime[ptr - 1] * 2 << endl; 
        }
    }
    return 0;
}