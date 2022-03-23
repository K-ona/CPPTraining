// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
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

class Solution {
 public:
  void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size(); 
    for (int i = 0; i <= n / 2; ++i) {
      if (n - 2 * i > 1)
        process(i, i, n - i * 2, matrix); 
    }
  }

  void process(int ltx, int lty, int len, vector<vector<int>>& matrix) {
    for (int i = 0; i < len - 1; ++i) {
      int x = 0; 
      int y = i; 
      int tmp = matrix[ltx + x][lty + y]; 
      for (int j = 0; j < 4; ++j) {
        int tmpx = x;
        x = y; 
        y = len - tmpx - 1; 
        // cout << tmp << " " << matrix[ltx + x][lty + y] << endl; 
        std::swap(tmp, matrix[ltx + x][lty + y]);
      }
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

  // std::vector<vector<int>> m = {{1,2,3},{4,5,6},{7,8,9}}; 
  std::vector<vector<int>> m = {{5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16}}; 
  Solution().rotate(m); 

  return 0;
}