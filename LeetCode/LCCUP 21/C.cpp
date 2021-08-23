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
    int magicTower(vector<int> nums) {
        long long sum = 0; 
        priority_queue<int> Q; 
        for (auto x: nums) {
            sum += x; 
        }
        if (sum <= -1) return -1; 

        int ans = 0; 
        sum = 0; 
        for (auto x: nums) {
            sum += x; 
            if (x < 0) Q.push(-x); 
            if (sum <= -1) {
                while (Q.size() && sum <= -1) {
                    sum += Q.top(); Q.pop(); ans++; 
                }
                if (Q.empty() && sum <= -1) {
                    return -1; 
                }
            }
        }
        return ans; 
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
    cout << app.magicTower({100,100,100,-250,-60,-140,-50,-50,100,150}) << endl; 
    return 0;
}