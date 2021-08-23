//created by Kona @VSCode
#include <iostream>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::cout;
using std::endl;

ll qpow(ll x, ll q, ll mod = 1e9 + 7) {
    ll res = 1; 
    while (q) {
        if (q & 1) {
            res *= x; 
            res %= mod; 
        }
        x *= x;
        x %= mod;
        q >>= 1;
    }
    return res;
}


class Solution {
public:
    int maxNiceDivisors(int primeFactors) {
        if (primeFactors <= 3) {
            return primeFactors; 
        }
        switch (primeFactors % 3)
        {
        case 0:
            /* code */
            return qpow(3, primeFactors / 3); 
            break;
        case 1:
            return qpow(3, primeFactors / 3 - 1) * 4 % ll(1e9 + 7); 
            break; 
        case 2:
            return qpow(3, primeFactors / 3) * 2 % ll(1e9 + 7);
            break; 
        default:
            break;
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */

    return 0;
}