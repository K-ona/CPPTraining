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

int dx, dy, n; 
map<pair<int, int>, int> Map;
int ddx[] = {1, 0, -1, 0};
int ddy[] = {0, 1, 0, -1};
map<pair<int, int>, int> vis; 

struct node
{
    int x, y; 
    int cnt; 
};

queue<node> Q; 

int BFS(int x, int y) {
    Q.push({x, y, 0}); 
    int ans = 0; 
    while(!Q.empty()) {
        node tmp = Q.front(); Q.pop(); 
        if (tmp.x == dx && tmp.y == dy) {
            ans = tmp.cnt; 
            break; 
        }

        for (int i = 0; i < 4; i++) {
            if (Map[{tmp.x + ddx[i], tmp.y + ddy[i]}] == 0 && vis[{tmp.x + ddx[i], tmp.y + ddy[i]}] == 0) {
                Q.push({tmp.x + ddx[i], tmp.y + ddy[i], tmp.cnt + 1}); 
                vis[{tmp.x + ddx[i], tmp.y + ddy[i]}]++; 
            }
        }
    }
    return ans; 
}

int main()
{
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */
    
    while (cin >> dx >> dy >> n)
    {
        // memset(dp, -1, sizeof(dp)); 
        while(n--) {
            int x, y; 
            cin >> x >> y; 
            Map[{x, y}]++; 
        }
        cout << BFS(0, 0) << endl;
    }
    
    return 0;
}