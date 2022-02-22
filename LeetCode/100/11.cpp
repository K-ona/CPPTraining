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
  int maxArea(vector<int>& height) {
    int l = 0, r = height.size(); 
    int res = 0; 
    while (l < r) {
      res = std::max(res, std::min(height[l], height[r]) * (r - l)); 
      height[l] <= height[r] ? ++l : --r;
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