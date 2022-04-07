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
  bool rotateString(string s, string goal) {
    if (s.size() != goal.size())
      return false;
    for (int begin = 0; begin < s.size(); ++begin) {
      while (begin < s.size() and s[begin] != goal[0]) {
        ++begin;
      }
      if (begin == s.size())
        return false;
      int i = 0; 
      for (int j = begin; i < s.size(); ++i) {
        if (s[(j + i) % s.size()] != goal[i])
          break;
      }
      if (i == s.size())
        return true;
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