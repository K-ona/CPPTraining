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
    vector<int> selfDividingNumbers(int left, int right) {
      vector<int> res;
      res.reserve(right - left + 1);
      for (int i = left; i <= right; ++i) {
        int tmp = i;
        while (tmp) {
          if (tmp % 10 == 0 or i % (tmp % 10) != 0) {
            break;
          }
          tmp /= 10; 
        }
        if (tmp == 0) {
          res.push_back(i);
        }
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