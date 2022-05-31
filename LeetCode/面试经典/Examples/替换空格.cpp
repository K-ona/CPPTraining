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
   * @param s: the given string
   * @return: same as s but space replaced by "%20"
   */
  string replaceSpace(string s) {
    int cnt = 0; 
    for (auto c: s) {
      if (c == ' ') ++cnt;
    }
    string res(s.size() + cnt * 2, ' '); 
    cnt = 0; 
    for (auto c: s) {
      if (c != ' ') res[cnt++] = c; 
      else {
        res[cnt++] = '%';
        res[cnt++] = '2';
        res[cnt++] = '0';
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