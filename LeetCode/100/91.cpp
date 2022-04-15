// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
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

std::map<int, int> cnt; 
class Solution {
  std::string s;
public:
    int numDecodings(string s) {
      cnt = {}; 
      this->s = s;
      return DFS(0); 
    }

    int DFS(int pos) {
      if (cnt.find(pos) != cnt.end()) return cnt[pos];
      if (s[pos] == '0') return 0;
      if (pos == s.size()) return 1;
      if (pos == s.size() - 1) return 1;
      if (pos > s.size()) return 0;

      int res = 0;
      if (s[pos] > '2' or (pos + 1 < s.size() and s[pos] == '2' && s[pos + 1] > '6')) res += DFS(pos + 1);
      else {
        res += DFS(pos + 1);
        res += DFS(pos + 2);
      }
      return cnt[pos] = res; 
    }
};





int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */
  std::cout << Solution().numDecodings("111111111111111111111111111111111111111111111") << std::endl;

  return 0;
}