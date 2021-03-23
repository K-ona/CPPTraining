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
class Solution {
public:
    vector<double> getCollisionTimes(vector<vector<int>>& cars) {
        int n = cars.size(); 
        stack<int> S; 
        vector<double> ans(n, -1); 
        auto calc = [&](int i, int j){ // 第i辆车追上第j辆车所用的时间
            return 1.0 * (cars[j][0] - cars[i][0]) / (cars[i][1] - cars[j][1]);
        };

        for (int i = n - 1; ~i; i--)
        {
            while(!S.empty())
            {
                if (cars[i][1] <= cars[S.top()][1]) S.pop(); 
                else 
                {
                    auto t = calc(i, S.top()); 
                    if (ans[S.top()] == -1 || t <= ans[S.top()])
                    {
                        ans[i] = t; 
                        break; 
                    }
                    else S.pop(); 
                }
            }
            S.push(i); 
        }
        return ans; 
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
    vector<vector<int>> M{{3,4},{5,4},{6,3},{9,1}}; 
    app.getCollisionTimes(M); 
    return 0;
}