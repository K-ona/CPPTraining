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


int dp[105][105]; 
int head[105]; //初始化-1

struct P
{
    int to;
    int cost;
    int next;
}Edge[405];

void add_edge(int u, int v, int c, int i)
{
    Edge[i].to = v;
    Edge[i].cost = c;
    Edge[i].next = head[u];
    head[u] = i;
}

class Solution {
    int Vol; 
    int Fin; 
public:
    int electricCarPlan(vector<vector<int>> paths, int cnt, int start, int end, vector<int> charge) {
        memset(head, -1, sizeof head); 
        memset(dp, -1, sizeof dp); 
        Vol = cnt; Fin = end; 

        for (int i = 0; i < paths.size(); i++) {
            add_edge(paths[i][0], paths[i][1], paths[i][2], i * 2); 
            add_edge(paths[i][1], paths[i][0], paths[i][2], i * 2 + 1); 
        }
        stack<int> St; St.push(start); 
        return DFS(start, 0, charge, St); 
    }
    
    int DFS(int s, int cur, vector<int> &charge, stack<int> &St) {

        if (~dp[s][cur]) {
            St.pop(); 
            return dp[s][cur]; 
        }

        if (St.size() > 1) {
            St.pop(); 
            cout << St.top() << "->" << s << " " << cur << endl; 
            St.push(s); 
        }

        if (s == Fin)  {
            St.pop(); 
            return dp[s][cur] = 0; 
        }

        int res = 1e9; 
        for (int i = head[s]; ~i; i = Edge[i].next) {
            // if (s == 1) {
            //     cout << Edge[i].to << endl; 
            // }
            bool flag = false; 
            stack<int> tmp = St; 

            while (!St.empty()) {
                if (St.top() == Edge[i].to) {
                    flag = true; 
                }
                // if (s == 2) {
                    // cout << St.top() << " "; 
                // }
                St.pop(); 
            }
            // cout << endl; 

            St = tmp;
            
            if (flag) continue; 

            if (Vol >= Edge[i].cost) {
                // if (s == 2) {
                //     cout << Edge[i].to << " in 1 " << endl; 
                // }
                St.push(Edge[i].to); 
                res = min (abs(res), abs(Edge[i].cost + DFS(Edge[i].to, Vol - Edge[i].cost, charge, St) + (Vol - cur) * charge[s])); 
            }
            
            if (cur < Edge[i].cost && Vol > Edge[i].cost) {
                // if (s == 2) {
                //     cout << Edge[i].to << " in 2 " << endl; 
                // }
                St.push(Edge[i].to); 
                res = min(abs(Edge[i].cost + DFS(Edge[i].to, 0, charge, St) + (Edge[i].cost - cur) * charge[s]), 
                            abs(res));
            }
            if (cur >= Edge[i].cost) {
                // if (s == 2) {
                //     cout << Edge[i].to << " in 3 " << endl; 
                // }
                St.push(Edge[i].to); 
                res = min(abs(Edge[i].cost + DFS(Edge[i].to, cur - Edge[i].cost, charge, St)), 
                            res);
            }
        }
        St.pop(); 
        cout << "res : " << s << " " << cur << " " << res << endl; 
        return dp[s][cur] = res; 
    }
};

int main() {
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */
    Solution app; 
    
    // cout << app.electricCarPlan({{1,3,3},{3,2,1},{2,1,3},{0,1,4},{3,0,5}}, 6, 1, 0, {2, 10, 4, 1}) << endl; 
    cout << app.electricCarPlan({{0,4,2},{4,3,5},{3,0,5},{0,1,5},{3,2,4},{1,2,8}}, 8, 0, 2, {2, 10, 4, 1}) << endl; 

    return 0;
}