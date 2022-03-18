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

int sum[20005];
class Solution {
 public:
  int trap(vector<int>& height) {
    std::queue<int> Q;
    int n = height.size();
    sum[0] = height[0];
    for (int i = 1; i < n; ++i)
      sum[i] = sum[i - 1] + height[i];
    int pre = 0;
    int res = 0;
    for (int i = 0; i < n; ++i) {
      if (height[i] >= height[pre]) {
        res += height[pre] * (i - pre - 1) - sum[i] + sum[pre] + height[i];
        pre = i;
      }
    }

    int suf = n - 1;
    for (int i = n - 1; i >= pre; --i) {
      if (height[i] >= height[suf]) {
        res += height[suf] * (suf - i - 1) + sum[i] - sum[suf] + height[suf];
        suf = i;
      }
    }
    return res;
  }
  int trap_dp(vector<int>& height) {
    int n = height.size();
    if (n == 0) {
      return 0;
    }
    vector<int> leftMax(n);
    leftMax[0] = height[0];
    for (int i = 1; i < n; ++i) {
      leftMax[i] = max(leftMax[i - 1], height[i]);
    }

    vector<int> rightMax(n);
    rightMax[n - 1] = height[n - 1];
    for (int i = n - 2; i >= 0; --i) {
      rightMax[i] = max(rightMax[i + 1], height[i]);
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
      ans += min(leftMax[i], rightMax[i]) - height[i];
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