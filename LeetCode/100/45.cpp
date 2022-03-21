// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
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
  std::vector<int> d;

 public:
  int jump(vector<int>& nums) {
    int n = nums.size();
    d.reserve(n);
    std::set<int> S;
    S.insert(n - 1);
    d[n - 1] = 0;
    for (int i = n - 2; i >= 0; --i) {
      if (i + nums[i] >= *S.begin()) {
        auto ptr = S.lower_bound(i + nums[i]);
        if (ptr == S.end() or *ptr != i + nums[i])
          --ptr;
        d[i] = d[*ptr] + 1;
        for (auto it = S.begin(); it != S.end() and *it <= i + nums[i];) {
          if (d[i] <= d[*it]) {
            S.erase(it++);
          } else {
            ++it;
          }
        }
        S.insert(i);
      }
    }
    return d[0];
  }

  int jump_1(vector<int>& nums) {
    int maxPos = 0, n = nums.size(), end = 0, step = 0;
    for (int i = 0; i < n - 1; ++i) {
      if (maxPos >= i) {
        maxPos = std::max(maxPos, i + nums[i]);
        if (i == end) {
          end = maxPos;
          ++step;
        }
      }
    }
    return step;
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