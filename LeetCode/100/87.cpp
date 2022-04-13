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
    bool isScramble(string s1, string s2) {
      std::map<std::pair<string, string>, int> mem; 
      return DFS(s1, s2, mem);
    }

    bool DFS(string s1, string s2, std::map<std::pair<string, string>, int>& mem) {
      if (mem.find({s1, s2}) != mem.end()) return mem[{s1, s2}];
      if (s1 == s2) return true;
      if (s1.size() != s2.size()) return false;
      int len = s1.size(); 
      vector<int> cnt(26, 0);
      for (int i = 0; i < len; ++i) {
        ++cnt[s1[i] - 'a'];
        --cnt[s2[i] - 'a'];
      }
      for (int i = 0; i < 26; ++i) {
        if (cnt[i] != 0) return false;
      }
      bool res = false;
      for (int i = 0; i < len - 1; ++i) {
        res = res || DFS(s1.substr(0, i + 1), s2.substr(0, i + 1), mem) &&
                  DFS(s1.substr(i + 1, len - i - 1), s2.substr(i + 1, len - i - 1), mem);
        res = res || DFS(s1.substr(0, i + 1), s2.substr(len - i - 1, i + 1), mem) &&
                  DFS(s1.substr(i + 1, len - i - 1), s2.substr(0, len - i - 1), mem);
      }
      return mem[{s1, s2}] += static_cast<int>(res); 
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