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
    bool isMatch(string s, string p) {
      int sp = 0; 
      int pp = 0;
      int sl = s.size(); 
      int pl = p.size(); 
      while (sp < sl and pp < pl) {
        if (p[pp] != '*') {
          if (s[sp] == p[pp] or p[pp] == '.')
            ++sp, ++pp; 
          else
            return false; 
        } else if (p[pp] == '*') {
          if (pp == 0) return false; 
          if (p[pp] )
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

  return 0;
}