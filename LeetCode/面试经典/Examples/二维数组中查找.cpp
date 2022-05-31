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
  /**
   * @param matrix: the given row & column sorted matrix
   * @param target: the given target to be matched
   * @return: true if target is in matrix or false
   */
  bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
    int n = matrix.size();
    if (n == 0)
      return false;
    int m = matrix[0].size();
    if (m == 0)
      return false;

    int x = 0, y = m - 1;
    while (x < n and y >= 0) {
      if (matrix[x][y] == target)
        return true;
      matrix[x][y] > target ? --y : ++x;
    }
    return false;
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