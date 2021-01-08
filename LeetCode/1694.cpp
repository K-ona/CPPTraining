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

string reformatNumber(string number) {
    int cnt = 0; 
    string res = ""; 
    for(int i = 0; i < number.size(); i++)
    {
        if(number[i] >= '0' && number[i] <= '9')
        {
            res.push_back(number[i]); 
            cnt++; 
            if(cnt % 3 == 0) res.push_back('-'); 
        }
    }
    if(res.back() == '-')
        res.pop_back(); 
    if(res[res.size() - 2] == '-')
        swap(res[res.size() - 2], res[res.size() - 3]); 
    return res; 
}

int main()
{
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */

    string s; 
    cin >> s; 
    cout << reformatNumber(s) << endl; 

    return 0;
}