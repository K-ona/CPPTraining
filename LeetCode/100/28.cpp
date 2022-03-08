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
  vector<int> get_next(std::string str) {
    vector<int> next(str.size());
    size_t m = str.size();
    int t = next[0] = -1;
    int i = 0;

    while (i < m - 1) {
      if (0 <= t and str[i] != str[t]) {
        t = next[t];
      } else {
        ++i;
        ++t;
        next[i] = t;
      }
    }
    return next;
  }

 public:
  int strStr(string T, string P) {
    int n = T.size(), i = 0;
    int m = P.size(), j = 0;
    if (!m)
      return 0;
    vector<int> next = get_next(P);
    while (i < n and j < m) {
      if (0 <= j and T[i] != P[j]) {
        j = next[j];
      } else {
        ++i;
        ++j;
      }
    }
    if (j == m)
      return i - j;
    return -1;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */
  cout << Solution().strStr("aaaaa", "bba") << endl;
  return 0;
}
