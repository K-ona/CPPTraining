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
    vector<vector<int>> subsets(vector<int>& nums) {
      int n = nums.size(); 
      vector<vector<int>> res;
      res.reserve(1 << n); 
      for (int vis = (1 << n) - 1; vis >= 0; --vis) {
        vector<int> tmp;
        tmp.reserve(10); 
        for (int i = 0; i < n; ++i) {
          if (vis & (1 << i)) tmp.push_back(nums[i]);
        }
        res.push_back(std::move(tmp));
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