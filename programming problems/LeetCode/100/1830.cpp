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

class Solution {
private:
    static constexpr int mod = 1000000007;
    using LL = long long;
    
public:
    int makeStringSorted(string s) {
        int n = s.size();
        
        // fac[i] 表示 i! mod m
        // facinv[i] 表示 i! 在 mod m 意义下的乘法逆元
        vector<int> fac(n + 1), facinv(n + 1);
        fac[0] = facinv[0] = 1;
        for (int i = 1; i < n; ++i) {
            fac[i] = (LL)fac[i - 1] * i % mod;
            // 使用费马小定理 + 快速幂计算乘法逆元
            facinv[i] = powmod(fac[i], mod - 2);
        }
        
        // freq 存储每个字符出现的次数
        vector<int> freq(26);
        for (char ch: s) {
            ++freq[ch - 'a'];
        }
        
        int ans = 0;
        for (int i = 0; i < n - 1; ++i) {
            // rank 求出比 s[i] 小的字符数量
            int rank = 0;
            for (int j = 0; j < s[i] - 'a'; ++j) {
                rank += freq[j];
            }
            // 排列个数的分子
            int cur = (LL)rank * fac[n - i - 1] % mod;
            // 依次乘分母每一项阶乘的乘法逆元
            for (int j = 0; j < 26; ++j) {
                cur = (LL)cur * facinv[freq[j]] % mod;
            }
            ans = (ans + cur) % mod;
            --freq[s[i] - 'a'];
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

    return 0;
}