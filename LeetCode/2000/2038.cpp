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
  bool winnerOfGame(string colors) {
    int cntA = 0; 
    int cntB = 0; 
    int n = colors.size(); 
    for (int i = 0; i < n; ++i) {
      if (i and colors[i - 1] == colors[i] and i + 1 < n and colors[i + 1] == colors[i]) {
        colors[i] == 'A' ? ++cntA : ++cntB; 
      }
    }
    if (cntA >= cntB) return true;
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