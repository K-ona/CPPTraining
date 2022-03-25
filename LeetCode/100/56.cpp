// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
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
  vector<vector<int>> merge(vector<vector<int>>& intervals) {
    vector<vector<int>> res;
    res.reserve(intervals.size()); 
    if (intervals.size() == 0) return res;
    sort(intervals.begin(), intervals.end());

    for (int i = 1; i < intervals.size(); i++) {
      if (intervals[i - 1][1] >= intervals[i][0]) {
        intervals[i][1] = std::max(intervals[i - 1][1], intervals[i][1]);
        intervals[i][0] = intervals[i - 1][0]; 
      } else {
        res.push_back(intervals[i - 1]); 
      }
    }
    res.push_back(intervals.back());
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