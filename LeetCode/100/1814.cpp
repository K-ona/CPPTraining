//created by Kona @VSCode
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>

// #define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::map;
using std::vector;
using std::string;
using std::cout;
using std::endl;

class Solution {
private:
    inline int rev(int x) {
        int res = 0;
        while (x) {
            res = res * 10 + x % 10;
            x /= 10; 
        }
        return res; 
    }
public:
    int countNicePairs(vector<int> nums) {
        // vector<int> arr; arr.reserve(nums.size()); 
        std::unordered_map<int, int> Map; 

        for (int i = 0; i < (int)nums.size(); ++i) {
            // arr.emplace_back(nums[i] - rev(nums[i])); 
            ++Map[nums[i] - rev(nums[i])]; 
        }
        int res = 0; 
        for (auto x: Map) {
            res += (1LL * x.second * (x.second - 1) / 2) % ((int)1e9 + 7); 
            res %= (int)1e9 + 7;
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

    Solution app; 
    cout << app.countNicePairs({1,1,10,10}) << endl; 
    return 0;
}