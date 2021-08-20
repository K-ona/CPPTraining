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
    string s;
    int num[15]; 
    int per[200][2]; 
    int cnt = 0; 
    rep(i, '0', '9' + 1)
    {
        rep(j, '0', '9' + 1)
        {
            per[cnt][0] = i;
            per[cnt++][1] = j;
        }
    }

    for(cin >> _; _-- && cin >> s;)
    {
        int ans = s.size(); 
        // Case 1: a = b
        memset(num, 0, sizeof(num)); 

        for(auto c: s)
        {
            num[c - '0']++; 
        }
        int maxnum = -1; 
        rep(i, 0, 10)
        {
            maxnum = max(maxnum, num[i]); 
        }
        ans = min(ans, (int)s.size() - maxnum); 
        // cout << "case 1 :" << ans << endl; 
        // Case 2: a != b
        rep(i, 0, cnt)
        {
            int index = 0; 
            for(auto c: s)
            {
                if(c == per[i][index % 2])
                {
                    index++;
                }
            }
            // cout << "index = " << index << endl; 
            index = index / 2 * 2; 
            ans = min(ans, (int)s.size() - index);
        }
        cout << ans << endl; 
    }
    return 0;
}