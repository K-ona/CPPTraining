//created by Kona @VSCode
#include <iostream>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::cout;
using std::endl;

class Solution {
public:
    int maxNiceDivisors(int primeFactors) {
        return primeFactors / 2 * (primeFactors - primeFactors / 2) % ll(1e9 + 7); 
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