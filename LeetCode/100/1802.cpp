//created by Kona @VSCode
#include <iostream>

// #define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::cout;
using std::endl;

class Solution {
public:
    ll maxValue(ll n, ll index, ll maxSum) {
        ll l = 1, r = maxSum; 
        ll res = 0; 
        while (l <= r) {
            ll mid = (l + r) >> 1; 
            if (check(mid, index, n, maxSum)) {
                res = mid; 
                l = mid + 1; 
            }
            else r = mid - 1; 
        }
        return res; 
    }

    bool check(ll mid, ll &ind, ll &n, ll &maxSum) {
        ll lsum = (mid + std::max(1LL, mid - ind)) *  std::min(mid, ind + 1) / 2 + std::max(0LL, ind - mid + 1);
        ll rsum = (mid + std::max(1LL, mid - (n - 1 - ind))) *  std::min(mid, n - ind) / 2 + std::max(0LL, n - ind - mid);
        ll sum = lsum + rsum - mid; 
        return sum <= maxSum; 
    }
};

int32_t main() {
    std::ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */

    Solution app;

    cout << app.maxValue(6, 2, 931384943) << endl; 
    return 0;
}