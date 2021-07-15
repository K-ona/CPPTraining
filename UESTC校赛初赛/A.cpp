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

int n; 
int resc = 0, nresc = 0;

int cal(string &s, char c) {
    int cntc = 0, ncntc = 0; 
    for (int i = 0; i < n; i++) {
        if (s[i] == c) {
            cntc++;
            if (cntc == 3) {
                resc += 3;
                cntc = 0; 
            }
        }
        else {
            if (cntc < 2 && i + 1 < n && s[i + 1] != c) {
                ncntc = 2; 
                cntc = 0;
                i++;  
                continue; 
            }
            if (i + 3 < n && s[i + 1] == c && s[i + 2] == c && s[i + 3] == c) {
                resc += 3; 
                i += 3; 
                continue; 
            }
            if (cntc == 2) {
                cntc = 0; 
                ncntc--; 
                resc += 2; nresc += 1; 
            }
            else if (cntc == 1 && i + 1 < n && s[i + 1] == c) {
                cntc = 0; 
                ncntc = 0; 
                resc += 2; nresc += 1; 
                i++; 
            }
            else if (cntc == 0 && i + 2 < n && s[i + 1] == c && s[i + 2] == c) {
                cntc = 0; 
                ncntc = 0; 
                resc += 2; nresc += 1; 
                i += 2; 
            }
            else {
                cntc = 0; 
            }
        }
    }
    return 0; 
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
    cin >> n;
    cin >> s; 
    int cnt1 = 0, cnt0 = 0; 
    for (auto c: s) {
        c == '0' ? cnt0++ : cnt1++; 
    }
    int ans = abs(cnt1 - cnt0); 
    cout << "ans1 == " << ans << endl; 
    resc = 0; nresc = 0; 
    cal(s, '1'); 
    ans = max(ans, abs(cnt1 - resc - cnt0 + nresc));
    cout << "ans2 == " << ans << endl; 
    resc = 0; nresc = 0; 
    cal(s, '0'); 
    ans = max(ans, abs(cnt0 - resc - cnt1 + nresc)); 
    cout << ans << endl; 
    return 0;
}