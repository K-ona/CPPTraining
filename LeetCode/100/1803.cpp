//created by Kona @VSCode
#include <iostream>
#include <vector>
#include <algorithm>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::cout;
using std::endl;

class Solution {
public:
    //  high >= num1 ^ num2 >= low
    // |a - b| <= a ^ b <= a + b
    int countPairs(std::vector<int>& nums, int low, int high) {
        std::sort(nums.begin(), nums.end(), std::greater<int>()); 
        
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