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

char M[][5] = {
  "",
  "",
  "abc", 
  "edf", 
  "ghi", 
  "jkl", 
  "mno", 
  "pqrs", 
  "tuv", 
  "wxyz"
}; 

class Solution {
 public:
  vector<string> letterCombinations(string digits) {
    if (digits.size() == 0) return vector<string>();
    vector<string> res[2] = {{""}}; 
    int cur = 0;
    for (auto d: digits) {
      for (auto &c: res[0]) {
        for (int i = 0; M[d - '0'][i]; ++i) {
          res[1].push_back(c + M[d - '0'][i]); 
        }
      }
      res[0] = res[1];
      res[1].clear(); 
    }
    return res[0]; 
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