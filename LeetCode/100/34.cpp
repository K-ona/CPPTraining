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
  vector<int> searchRange(vector<int>& nums, int target) {
    auto p1 = std::lower_bound(nums.begin(), nums.end(), target); 
    if (p1 == nums.end() or *p1 != target) return {-1, -1}; 

    auto p2 = std::lower_bound(p1, nums.end(), target + 1); 
    if (p2 == nums.end()) return {static_cast<int>(p1 - nums.begin()), static_cast<int>(nums.size()) - 1}; 
    return {static_cast<int>(p1 - nums.begin()), static_cast<int>(p2 - nums.begin() - 1)}; 
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