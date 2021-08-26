//created by Kona @VSCode
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <algorithm>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::map;
using std::vector;
using std::string;
using std::cout;
using std::endl;

class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        ll total = 0; 
        int l = 0, res = 1; 
        for (int r = 1; r < n; ++r) {
            total += 1LL * (nums[r] - nums[r - 1]) * (r - l);
            while (total > k) {
                total -= nums[r] - nums[l];
                ++l;
            }
            res = std::max(res, r - l + 1);
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