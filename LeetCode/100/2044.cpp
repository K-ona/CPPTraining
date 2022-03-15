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

int cnt[20];
class Solution {
 public:
  int countMaxOrSubsets(vector<int>& nums) {
    int max = 0, n = nums.size();
    for (auto x : nums) {
      max |= x;
    }
    for (int i = 0; i < 20; ++i) {
      for (int tar = 1 << i, j = 0; j < n; ++j) {
        if (max & tar) {
          ++cnt[i];
        }
      }
    }

    ll res = 1;
    for (int i = 0; i < 20; ++i) {
      if ((1 << i) & max) {
        res *= cnt[i];
      }
    }
    return res;
  }

  int countMaxOrSubsets_1(vector<int>& nums) {
    this->nums = nums;
    this->maxOr = 0;
    this->res = 0;
    dfs(0, 0);
    return res;
  }
  void dfs(int pos, int orVal) {
    if (pos == nums.size()) {
      if (orVal > maxOr) {
        maxOr = orVal;
        res = 1;
      } else if (orVal == maxOr) {
        res++;
      }
      return;
    }
    dfs(pos + 1, orVal | nums[pos]);
    dfs(pos + 1, orVal);
  }

 private:
  vector<int> nums;
  int maxOr, res;
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