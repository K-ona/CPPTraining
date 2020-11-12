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

vector<int> KMP(const string& S, const string& T)
{
    vector<int> Next;
    Next.push_back(-1);

    for (int i = 0, j = -1; i < T.size();) {
        if (j == -1 || T[i] == T[j]) {
            i++, j++;
            if (i != T.size() && T[j] == T[i]) Next.push_back(Next[j]);
            else Next.push_back(j);
        }
        else j = Next[j];
    }

    vector<int> res;
    for (int i = 0, j = 0; i < S.size() && j < (int)T.size();) {
        if (j == -1 || S[i] == T[j]) {
            i++, j++;
            if (j == T.size()) {
                res.push_back(i - j);
                j = Next[j];
            }
        }
        else j = Next[j];
    }

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
    string s, t; 
	cin >> s >> t;
	vector<int> res = KMP(s, t);
	for(auto pos:res)
	{
		cout << pos + 1 << ' ';
	}
    cout << endl; 
    return 0;
}