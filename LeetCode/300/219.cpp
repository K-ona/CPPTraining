#include <unordered_map>
#include <vector>

using std::unordered_map;
using std::vector;

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> M; 
        int min = 1e5; 
        for (int i = 0; i < nums.size(); ++i) {
            auto ptr = M.find(nums[i]); 
            if (ptr != M.end()) {
                min = std::min(i - ptr->second, min); 
                if (min <= k)
                    return true;
            }
            M[nums[i]] = i; 
        }
        return false;
    }
};