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
  vector<int> spiralOrder(vector<vector<int>>& matrix) {
    int n = matrix.size(); 
    int m = matrix[0].size();
    vector<int> res;
    res.reserve(n * m); 
    for (int i = 0, it_times = std::min(n / 2, m / 2); i <= it_times; ++i) {
       clockwise(matrix, i, i, n - i - i, m - i - i, res);
    }
    return res; 
  }

  void clockwise(vector<vector<int>>& matrix, int ltx, int lty, int n, int m, vector<int>& res) {
    if (n <= 0 or m <= 0) return;
    for (int i = 0; i < m; ++i) {
      res.push_back(matrix[ltx][lty + i]);
    }
    for (int i = 1; i < n; ++i) {
      res.push_back(matrix[ltx + i][lty + m - 1]);
    }
    if (n > 1)
    for (int i = m - 2; i >= 0; --i) {
      res.push_back(matrix[ltx + n - 1][lty + i]); 
    }
    if (m > 1)
    for (int i = n - 2; i > 0; --i) {
      res.push_back(matrix[ltx + i][lty]);
    }
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