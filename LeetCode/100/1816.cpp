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
  string truncateSentence(string s, int k) {
    int cnt = 0;
    int begin = -1;
    int end = -1;
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] != ' ' && begin == -1)
        begin = i;
      if (s[i] != ' ' && (i == s.size() || i < s.size() && s[i + 1] == ' ')) {
        ++cnt;
      }
      if (cnt == k) {
        end = 1 + i;
        break;
      }
    }
    return s.substr(begin, end);
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