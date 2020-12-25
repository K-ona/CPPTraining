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

const int maxn = 1e5 + 50; 
int a[maxn]; 

struct P
{
    /* data */
    int sum, index; 
    bool operator<(P A)
    {
        if(this->sum != A.sum)
        return this->sum < A.sum;
        return this->index < A.index; 
    }
};


int main()
{
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */
    // z不一定要用完
    // 

    int _, n, k, z; 

    for(cin >> _; cin >> n >> k >> z && _--;)
    { 
        vector<P> VP; 
        rep(i, 0, n) {cin >> a[i]; }
        rep(i, 1, n) {VP.pb({a[i - 1] + a[i], i}); }
        int maxindex = -1; 

        sort(all(VP)); 
        
        ll res = 0; 

        // cout << maxindex << " " << a[maxindex - 1] << " " << a[maxindex] << endl; 
        rep(j, 0, z + 1)
        {
            int z = j; 
            ll sum = a[0]; 
            int kk = k;
            int pos = 0; 
            maxindex = -1;
            for(auto x: VP)
            {
                // cout << x.first << " " << x.second << endl;
                if(x.index <= kk - 2 * z + 1)
                {
                    maxindex = x.index; 
                }
            }

            while(kk)
            {
                kk--; 
                sum += a[++pos]; 
                if(z > 0 && kk && pos == maxindex) 
                {
                    pos--; 
                    sum += a[pos]; 
                    // cout << a[pos] << endl; 
                    kk--;
                    z--;
                }
                
            }
            res = max(res, sum); 
        }
        
        cout << res << endl; 
    }

    return 0;
}