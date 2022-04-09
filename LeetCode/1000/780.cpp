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
  bool reachingPoints(int sx, int sy, int tx, int ty) {
    while (tx > sx && ty > sy && tx != ty) {
      if (tx > ty) {
        tx %= ty;
      } else {
        ty %= tx;
      }
    }
    if (tx == sx && ty == sy) {
      return true;
    } else if (tx == sx) {
      return ty > sy && (ty - sy) % tx == 0;
    } else if (ty == sy) {
      return tx > sx && (tx - sx) % ty == 0;
    } else {
      return false;
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