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
  string convert(string s, int numRows) {
    if (numRows == 1) return s;
    char sa[numRows][s.size()]; 
    int cnt[numRows]; 
    memset(cnt, 0, sizeof(cnt)); 
    for (int i = 0, flag = 1, j = -1; i < (int)s.size(); ++i) {
      j += flag; 
      sa[j][cnt[j]++] = s[i]; 
      if (i && (i % (numRows - 1) == 0)) {
        flag *= -1; 
      }
    }
    string res; 
    for (int i = 0; i < numRows; ++i) {
      res.append(sa[i]); 
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