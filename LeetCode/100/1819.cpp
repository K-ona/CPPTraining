//created by Kona @VSCode
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::map;
using std::vector;
using std::string;
using std::cout;
using std::endl;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}

class Solution {
public:
    int countDifferentSubsequenceGCDs(vector<int>& nums) {
        vector<int> g(*max_element(nums.begin(), nums.end()) + 1); 
        int res = 0; 
        for (auto x: nums) {
            for (int i = 1; i * i <= x; ++i) {
                if (x % i == 0) {
                    g[i] = g[i] == 0 ? x : gcd(x, g[i]); 
                    g[x/ i] = g[x/ i] == 0 ? x : gcd(x, g[x/ i]); 
                }
            }
            g[x] = g[x] == 0 ? x : gcd(x, g[x]); 
        }
        for (int i = 1; i < (int)g.size(); ++i) {
            res += g[i] == i; 
        }
        return res; 
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