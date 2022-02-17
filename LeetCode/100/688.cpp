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

double mem[30][30][105]; 

class Solution {
  int n; 
  int dx[8] = {1, 1, -1, -1, 2, 2, -2, -2}; 
  int dy[8] = {2, -2, 2, -2, 1, -1, -1, 1}; 
public:
    double knightProbability(int n, int k, int row, int column) {
        this -> n = n; 
        memset(mem, 0, sizeof mem); 
        return DFS(row, column, k); 
    }

    double DFS(int x, int y, int k) {
      if (k <= 0) return 1.;
      if (mem[x][y][k] != 0) return mem[x][y][k];
      double res = 0;
      for (int i = 0; i < 8; ++i) {
        if (isvalid(x, y, i)) {
          res += 1.0 / 8 * DFS(x + dx[i], y + dy[i], k - 1);
        }
      }
      return mem[x][y][k] = res;
    }

    bool isvalid(int x, int y, int i) {
      if (x + dx[i] < 0 or x + dx[i] >= n) return false; 
      if (y + dy[i] < 0 or y + dy[i] >= n) return false; 
      return true;
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