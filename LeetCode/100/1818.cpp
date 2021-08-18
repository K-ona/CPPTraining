//created by Kona @VSCode
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

// #define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::map;
using std::vector;
using std::string;
using std::cout;
using std::endl;

class Solution {
public:
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(); 
        auto nums3 = nums1; 
        std::sort(nums3.begin(), nums3.end()); 

        ll ans = 0; 
        int Mini = 0; 
        int curMin = INT32_MAX; 
        for (int i = 0; i < n; i++) {
            auto tmp = std::abs(nums1[i] - nums2[i]); 
            ans += tmp; 
            auto x = std::lower_bound(nums3.begin(), nums3.end(), nums2[i]) - nums3.begin(); 
            int Max = x == n ? INT32_MAX : nums3[x]; 
            int Min = x == 0 ? INT32_MAX : nums3[x - 1]; 
            if (std::min(std::abs(Max - nums2[i]), std::abs(Min - nums2[i])) - tmp <= curMin) {
                curMin = std::min(std::abs(Max - nums2[i]), std::abs(Min - nums2[i])) - tmp; 
                Mini = i; 
            }
        }
        auto x = std::lower_bound(nums3.begin(), nums3.end(), nums2[Mini]) - nums3.begin(); 
        int Max = x == n ? INT32_MAX : nums3[x];
        int Min = x == 0 ? INT32_MAX : nums3[x - 1]; 
        ans = ans - std::abs(nums1[Mini] - nums2[Mini]) + std::min(std::abs(Max - nums2[Mini]), std::abs(Min - nums2[Mini]));
        ans %= static_cast<int>(1e9 + 7); 
        return ans; 
    }
};

int main() {
    std::ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */
    vector<int> nums1{56,51,39,1,12,14,58,82,18,41,70,64,18,7,44,90,55,23,11,79,59,76,67,92,60,80,57,11,66,32,76,73,35,65,55,37,38,26,4,7,64,84,98,61,78,1,80,33,5,66,32,30,52,29,41,2,21,83,30,35,21,30,13,26,36,93,81,41,98,23,20,19,45,52,25,51,52,24,2,45,21,97,11,92,28,37,58,29,5,18,98,94,86,65,88,8,75,12,9,66}; 
    vector<int> nums2{64,32,98,65,67,40,71,93,74,24,49,80,98,35,86,52,99,65,15,92,83,84,80,71,46,11,26,70,80,2,81,57,97,12,68,10,49,80,24,18,45,72,33,94,60,5,94,99,14,41,25,83,77,67,49,70,94,83,55,17,61,44,50,62,3,36,67,10,2,39,53,62,44,72,66,7,3,6,80,38,43,100,17,25,24,78,8,4,36,86,9,68,99,64,65,15,42,59,79,66}; 
    Solution app; 
    cout << app.minAbsoluteSumDiff(nums1, nums2) << endl;  

    return 0;
}