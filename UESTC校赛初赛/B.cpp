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

map<int, int> Map1;
map<int, int> Map2;

int main()
{
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */
    int n1, n2; 
    while(cin >> n1) {
        rep(i, 0, n1) {
            int tmp; 
            cin >> tmp; 
            Map1[tmp]++;  
        }
        cin >> n2; 
        rep(i, 0, n2) {
            int tmp; 
            cin >> tmp; 
            Map2[tmp]++;  
        }
        if (Map1.size() == Map2.size()) {
            if (Map1 == Map2) {
                cout << "A equals B" << endl; 
                continue; 
            }
        }
        int cnt = 0;
        int sz1 = Map1.size();
        int sz2 = Map2.size();  
        for (auto it = Map1.begin(); it != Map1.end(); it++) {
            if (Map2[it->first]) {
                cnt++; 
            }
        }
        // cout << "cnt == " << cnt << endl; 
        if (cnt == sz1) {
            cout << "A is a proper subset of B" << endl; 
        }
        else if (cnt == sz2){
            cout << "B is a proper subset of A" << endl; 
        }
        else if (cnt == 0) {
            cout << "A and B are disjoint" << endl; 
        }
        else {
            cout << "I am confused!" << endl;
        }
    }
    return 0;
}