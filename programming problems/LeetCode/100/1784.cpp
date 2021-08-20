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
    bool checkOnesSegment(string s) {
        std::regex ex("1+"); 
        auto words_begin = 
        std::sregex_iterator(s.begin(), s.end(), ex);
        auto words_end = std::sregex_iterator();
        // std::cout << std::distance(words_begin, words_end) << std::endl; 

        if (std::distance(words_begin, words_end) > 2) {
            return false; 
        }
        return true; 
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
    while (true) {
        string s; 
        cin >> s; 
        app.checkOnesSegment(s); 
    }

    return 0;
}