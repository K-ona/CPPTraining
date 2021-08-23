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

class Solution {
public:
    int cnt[26][2]; 
    int minCharacters(string a, string b) 
    {
        int res = func(a, b);  
        // int tmp1 = func(a, b); 
        // int tmp2 = func(b, a); 
        int Max = 0; 
        for (int i = 0; i < 26; i++)
        {
            Max = max(Max, cnt[i][0] + cnt[i][1]); 
        }
        return min(res, (int)a.size() + (int)b.size() - Max); 
    }

    int func(string a, string b)
    {
        memset(cnt, 0, sizeof(cnt)); 
        for (auto c: a)
        {
            cnt[c - 'a'][0]++; 
        }
        for (auto c: b)
        {
            cnt[c - 'a'][1]++; 
        }
        int res = 1e9; 
        for (char sep = 'b'; sep <= 'z'; sep++)
        {
            int op1 = 0, op2 = 0;
            for (int i = 0; i < 26; i++)
            {
                if ('a' + i >= sep)
                    op1 += cnt[i][0], op2 += cnt[i][1]; 
                if ('a' + i < sep)
                    op1 += cnt[i][1], op2 += cnt[i][0]; 
            }
            res = min(min(op1, op2), res); 
        }
        return res; 
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

    Solution app; 
    cout << app.minCharacters("a", "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz") << endl; 

    return 0;
}