#include <vector>
#include <algorithm>

using std::vector; 
using std::pair;

class Solution {
public:
    vector<int> findRightInterval(vector<vector<int>>& intervals) {
        vector<pair<int, int>> VP; 
        VP.reserve(20000); 
        int cnt = 0; 
        for (const auto& x: intervals) {
            VP.push_back({x[0], cnt++}); 
        }
        std::sort(VP.begin(), VP.end()); 
        vector<int> res; 
        res.reserve(20000); 
        auto cmp = [](const auto& item, const auto& target) {
              return item.first < target;
        }; 
        for (const auto& x: intervals) {
            auto p = std::lower_bound(VP.begin(), VP.end(), x[1], cmp);
            if (p != VP.end()) 
                res.push_back(p->second); 
            else 
                res.push_back(-1);
        }
        return res; 
    }
};