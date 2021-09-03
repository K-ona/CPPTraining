// created by Kona @VSCode
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::map;
using std::vector;
using std::string;
using std::cout;
using std::endl;

class Solution {
    // int dp[30005];
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size(); 
        // dp[0] = nums[0]; 
        for (int i = 1; i < n; ++i) {
            nums[i] = std::max(nums[i], nums[i - 1] + nums[i]); 
        }        
        return *std::max_element(nums.begin(), nums.end()); 
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