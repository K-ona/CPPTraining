//created by Kona @VSCode
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <set>

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
    vector<int> findingUsersActiveMinutes(vector<vector<int>>& logs, int k) {
        vector<int> res; res.reserve(k + 1); 
        std::unordered_map<int, std::set<int>> uMap; 
        std::unordered_map<int, int> cnt; 
        for (auto x: logs) {
            uMap[x[1]].insert(x[0]); 
        }
        for (auto x: uMap) {
            for (auto y: x.second) {
                cnt[y]++; 
            }
        }
        for (auto x: cnt) {
            res[x.second]++; 
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