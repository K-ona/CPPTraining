// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::queue;
using std::string;
using std::vector;

class Solution {
 public:
  int getMinDistance(vector<int>& nums, int target, int start) {
    vector<std::pair<int, int>> tmp;
    tmp.reserve(nums.size());
    for (int i = 0; i < nums.size(); ++i) {
      tmp.push_back({nums[i], i});
    }
    std::sort(tmp.begin(), tmp.end());
    auto begin_pos =
        std::lower_bound(tmp.begin(), tmp.end(), std::pair{target, -1}) -
        tmp.begin();
    auto end_pos =
        std::lower_bound(tmp.begin(), tmp.end(), std::pair{target + 1, -1}) -
        tmp.begin();
    auto canditate = std::lower_bound(tmp.begin(), tmp.end(), start,
                                      [](auto first, auto second) -> bool {
                                        return first.second < second.second;
                                      }) -
                     tmp.begin();

    if (canditate == end_pos)
      return abs(tmp[canditate - 1].second - start);
    if (canditate == begin_pos)
      return abs(tmp[canditate].second - start);
    if (tmp[canditate].second == start)
      return 0;
    return std::min(abs(tmp[canditate].second - start),
                    abs(tmp[canditate - 1].second - start));
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