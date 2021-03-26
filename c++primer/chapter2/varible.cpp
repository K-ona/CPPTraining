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

// extern int x = 1; 

int __X; 

int main()
{
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */

    // extern int x; 
    // cout << x << endl; 

    // int x = 1; 
    // double &y = x; 
    
    // int &z = 50; 
    // const int &z = 50; 

    // int &z = 1 + 2;
    const int &z = 1 + 2; 

    double y = 0.5; 
    const int &x = y; 

    cout << y << endl;  
    cout << (1 and 0) << endl; 
    int n; 
    cout << n << endl; 

    const int &ci = 1; 
    // int &c2 = 1; error
    double d1 = 1.9;  
    int d2 = 2; 
    // int &c1 = d; error
    const int &c1 = d1; 
    const int &c2 = d2; 

    cout << &c1 << " " << &d1 << endl;  
    cout << &c2 << " " << &d2 << endl;  
    
    cout << ci << endl; 
    return 0;
}