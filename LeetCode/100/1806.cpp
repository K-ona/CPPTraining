//created by Kona @VSCode
#include <iostream>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::cout;
using std::endl;

class Solution {
public:
    int reinitializePermutation(int n) {
        int ind = 1, cnt = 1; 
        while (!(cnt > 1 && ind == 1)) {
            if (ind < n / 2) {
                ind *= 2; 
            }
            else {
                ind = 2 * ind - n + 1; 
            }
        }
        return cnt;
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