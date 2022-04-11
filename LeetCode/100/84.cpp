// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>

#include <string.h>

// #define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::queue;
using std::string;
using std::vector;

int stk[100005]; 
class Solution {
 public:
  int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    vector<int> left(n, 0);
    vector<int> right(n, n - 1);
    int top = -1;
    for (int i = 0; i < n; ++i) {
      while (top != -1 && heights[stk[top]] > heights[i]) {
        right[stk[top--]] = i - 1;
      }
      stk[++top] = i;
    }
    top = -1;
    for (int i = n - 1; i >= 0; --i) {
      while (top != -1 && heights[stk[top]] > heights[i]) {
        left[stk[top--]] = i + 1;
      }
      stk[++top] = i;
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      ans = std::max(ans, (right[i] - left[i] + 1) * heights[i]);
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

  // Solution().largestRectangleArea({2,1,5,6,2,3});

  return 0;
}