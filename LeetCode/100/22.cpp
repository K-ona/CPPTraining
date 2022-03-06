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
  vector<string> generateParenthesis(int n) {
    map<int, vector<string>> Map; 
    return DFS(n, Map); 
  }

  vector<string> DFS(int n, map<int, vector<string>>& Map) {
    if (Map[n].size()) return Map[n];
    vector<string> res; 
    if (!n)  {
      res.push_back(""); 
      return res;
    }
    for (int i = 0; i < n; ++i) {
      auto tmpi = DFS(i, Map); 
      auto tmpj = DFS(n - 1 - i, Map); 
      for (auto &s1: tmpi) {
        for (auto &s2: tmpj) {
          res.emplace_back("(" + s1 + ")" + s2); 
        }
      }
    }
    return Map[n] = res; 
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