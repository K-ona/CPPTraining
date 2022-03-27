// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>

#include <string.h>

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
  vector<vector<int>> insert(vector<vector<int>>& intervals,
                             vector<int>& newInterval) {
    vector<vector<int>> ans;
    ans.reserve(intervals.size() + 1); 
    auto ptr = std::lower_bound(
        intervals.begin(), intervals.end(), newInterval,
        [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });

    intervals.insert(ptr, newInterval);

    for (const auto &x : intervals) {
      if (ans.empty() or ans.back()[1] < x[0]) {
        ans.emplace_back(x);
      } else {
        ans.back()[1] = std::max(ans.back()[1], x[1]);
      }
    }
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

  return 0;
}