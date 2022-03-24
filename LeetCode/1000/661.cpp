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
  int dx[9] = {0, 0, 0, 1, -1, 1, -1, 1, -1};
  int dy[9] = {0, 1, -1, 0, 0, -1, 1, 1, -1};
 public:
  vector<vector<int>> imageSmoother(vector<vector<int>>& img) {
    auto img1 = img; 
    int n = img.size(), m = img[0].size();
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
       int sum = 0, cnt = 0;
        for (int k = 0; k < 9; ++k) {
          int x = i + dx[k], y = j + dy[k];
          if (x < 0 || x >= n || y < 0 || y >= m) continue;
          sum += img[x][y];
          cnt++;
        }
        img1[i][j] = sum / cnt;
      }
    }
    return img1;
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