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
    int n, k; 
    int l[3], r[3]; 

    for(cin >> _; _--;)
    {
        cin >> n >> k; 
        cin >> l[1] >> r[1]; 
        cin >> l[2] >> r[2]; 

        ll get = 0, ans = INT_MAX; 
        if(min(r[1], r[2]) >= max(l[1], l[2]))
        {
            get = 1LL * n * (min(r[1], r[2]) - max(l[1], l[2])); 
            int sep = max(r[1], r[2]) - min(l[1], l[2]) 
                      -(min(r[1], r[2]) - max(l[1], l[2])); 

            if(k - get <= 0)
            {
                ans = 0; 
            }
            else if(1LL * n * sep >= k - get)
            {
                ans = k - get; 
            }
            else 
            {
                ans = 1LL * n * sep + (k - get - n * sep) * 2; 
            }
        }
        else 
        {
            int sep = max(l[1], l[2]) - min(r[1], r[2]);  
            int get = max(r[1], r[2]) - min(l[1], l[2]);
            rep(i, 1, n + 1)
            {
                ll curans = 1LL * sep * i; 
                if(1LL * i * get >= 1LL * k)
                {
                    curans += k; 
                }
                else 
                {
                    curans += 1LL * i * get + (k - i * get) * 2;
                }
                ans = min(ans, curans); 
            }   
        }
        cout << ans << endl; 
    } 
    return 0;
}