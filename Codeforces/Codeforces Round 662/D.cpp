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

string b[2005]; 
int res[2005][2005][2]; 
int cnt_up[2005][2005], cnt_dw[2005][2005]; 

int main() {
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */

    int n, m; 
    cin >> n >> m; 
    rep (i, 0, n) {
        cin >> b[i]; 
    }

    rep (j, 0, m) {
        rep (i, 0, n) {
            if (i != 0 && b[i - 1][j] == b[i][j]) {
                cnt_up[i][j] = cnt_up[i - 1][j] + 1; 
            }
            else {
                cnt_up[i][j] = 1; 
            }   
            res[i][j][0] = res[i][j][1] = 1; 
        }
        per (i, 0, n) { 
            if (i != n -1 && b[i + 1][j] == b[i][j]) {
                cnt_dw[i][j] = cnt_dw[i + 1][j] + 1; 
            }
            else {
                cnt_dw[i][j] = 1; 
            }
        }
    }

    rep (j, 1, m) {
        rep (i, 1, n) {
            if (b[i - 1][j] == b[i][j] && b[i][j] == b[i][j - 1]) {
                int Max = min(res[i][j - 1][0] + 1, res[i - 1][j][0] + 1); 
                int Min = min(Max, cnt_dw[i][j]); 
                res[i][j][0] = Min; 
            }
        }
    }

    per (j, 0, m - 1) {
        rep (i, 1, n) {
            if (b[i - 1][j] == b[i][j] && b[i][j] == b[i][j + 1]) {
                int Max = min(res[i][j + 1][1] + 1, res[i - 1][j][1] + 1); 
                int Min = min(cnt_dw[i][j], Max); 
                res[i][j][1] = Min; 
            }
        }
    }

    ll ans = 0; 
    rep (i, 0, n) {
        rep (j, 0, m) {
            ans += min(res[i][j][1], res[i][j][0]); 
        }
    }
    cout << ans << endl; 

    return 0;
}


// #include <cstdio>
// int min(int a,int b){
// 	return a<b?a:b;
// }
// int min_4(int a,int b,int c,int d){
// 	return min(min(a,b),min(c,d));
// }
// const int Maxn=2000;
// typedef long long ll;
// int n,m;
// char mp[Maxn+5][Maxn+5];
// int f[Maxn+5][Maxn+5];
// int main(){
// 	scanf("%d%d",&n,&m);
// 	for(int i=1;i<=n;i++){
// 		scanf("%s",mp[i]+1);
// 	}
// 	ll ans=0;
// 	for(int i=3;i<=n;i++){
// 		for(int j=2;j<m;j++){
// 			if(mp[i-2][j]==mp[i][j]&&mp[i-1][j-1]==mp[i][j]&&mp[i-1][j]==mp[i][j]&&mp[i-1][j+1]==mp[i][j]){
// 				f[i][j]=min_4(f[i-2][j],f[i-1][j-1],f[i-1][j],f[i-1][j+1])+1;
// 				ans+=f[i][j];
// 			}
// 		}
// 	}
// 	printf("%lld\n",ans+n*m);
// 	return 0;
// }
