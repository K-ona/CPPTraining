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
    int minCharacters(string a, string b) 
    {
        
    }

    int func(string a, string b)
    {
        int cnt[30][2]; 
        for (auto c: a)
        {
            cnt[c - 'a'][0]++; 
        }
        for (auto c: b)
        {
            cnt[c - 'a'][1]++; 
        }
        int res = 0; 
        cnt[0][0] += cnt[25][0]; 
        res += cnt[25][0]; 
        cnt[25][0] = 0; 
        
        cnt[25][1] += cnt[0][1]; 
        res += cnt[0][1]; 
        cnt[0][1] = 0; 

        
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


    return 0;
}