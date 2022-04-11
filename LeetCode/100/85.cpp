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
  int maximalRectangle(vector<vector<char>>& matrix) {
    int m = matrix.size();
    if (m == 0) {
      return 0;
    }
    int n = matrix[0].size();
    vector<vector<int>> left(m, vector<int>(n, 0));

    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (matrix[i][j] == '1') {
          left[i][j] = (j == 0 ? 0 : left[i][j - 1]) + 1;
        }
      }
    }

    int ret = 0;
    for (int j = 0; j < n; j++) {  // 对于每一列，使用基于柱状图的方法
      vector<int> up(m, 0), down(m, 0);

      stack<int> stk;
      for (int i = 0; i < m; i++) {
        while (!stk.empty() && left[stk.top()][j] >= left[i][j]) {
          stk.pop();
        }
        up[i] = stk.empty() ? -1 : stk.top();
        stk.push(i);
      }
      stk = stack<int>();
      for (int i = m - 1; i >= 0; i--) {
        while (!stk.empty() && left[stk.top()][j] >= left[i][j]) {
          stk.pop();
        }
        down[i] = stk.empty() ? m : stk.top();
        stk.push(i);
      }

      for (int i = 0; i < m; i++) {
        int height = down[i] - up[i] - 1;
        int area = height * left[i][j];
        ret = max(ret, area);
      }
    }
    return ret;
  }
};

// 作者：LeetCode-Solution
// 链接：https://leetcode-cn.com/problems/maximal-rectangle/solution/zui-da-ju-xing-by-leetcode-solution-bjlu/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  return 0;
}