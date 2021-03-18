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
    int cnt[7][2]; 
public:
    int minOperations(vector<int>& nums1, vector<int>& nums2) {
        memset(cnt, 0, sizeof cnt); 
        int sum1 = 0, sum2 = 0; 
        for (auto num: nums1) {
            cnt[num][0]++; 
            sum1 += num; 
        }
        for (auto num: nums2) {
            cnt[num][1]++;
            sum2 += num;  
        }
        int x = 0, y = 1; 
        if (sum2 < sum1) swap(x, y), swap(sum1, sum2); 
        
        int ans = 0; 
        for (int i = 1; i < 7; i++) {
            int sep = cnt[i][x] * (6 - i) + cnt[7 - i][y] * (6 - i);
            if (sum1 + sep >= sum2) {
                ans += ceil(1. * (sum2 - sum1) / (6 - i)); 
                sum1 = sum2; 
                break; 
            }
            else {
                ans += cnt[i][x] + cnt[7 - i][y]; 
                sum1 += sep; 
            }
        }
        if (sum1 == sum2) return ans;
        else return -1; 
    }
};

int main() {
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */ 
    cout << ceil(11 / 5) << endl; 
    return 0;
}