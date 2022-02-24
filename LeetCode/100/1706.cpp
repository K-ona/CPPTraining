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
  vector<int> findBall(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<int> res(m, -2);
    for (int j = 0; j < m; ++j) {
      int k = j;
      for (int i = 0; i < n; ++i) {
        // cout << i << " " << k << endl; 
        if (grid[i][k] == 1 and k + 1 < m and grid[i][k + 1] == 1) {
          k += 1;
        } else if (grid[i][k] == -1 and k and grid[i][k - 1] == -1) {
          k -= 1;
        } else {
          res[j] = -1;
          break;
        }
      }
      res[j] = (~res[j]) ? k : -1;
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