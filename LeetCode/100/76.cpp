// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>
#include <unordered_map>

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
  string minWindow(string s, string t) {
    int l = 0, r = 0;  
    int ansl = 0, ansr = 0;
    vector<int> vis(256);
    std::unordered_map<char, int> M; 
    int ans = s.size() + 1; 

    for (auto c: t) {
      M[c]++;
      vis[c] = 1; 
    }

    while (r < s.size()) {
      if (vis[s[r]]) {
        M[s[r]]--;
      }
      r++; 
      while (l < r and check(M)) {
        if (vis[s[l]]) {
          M[s[l]]++;
          if (ans > r - l) {
            ans = r - l;
            ansl = l;
            ansr = r;
          }
          if (!check(M)) {
            ++l; 
            break;
          }
        }
        l++; 
      }
    }
    return s.substr(ansl, ansr - ansl);
  }

  bool check(std::unordered_map<char, int>& M) {
    bool flag = true;
    for (int i = 0; i < 26; ++i) {
      if (M[i + 'a'] > 0 or M[i + 'A'] > 0) {
        flag = false;
        break;
      }
    }
    return flag; 
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  Solution().minWindow("a", "a");
  return 0;
}