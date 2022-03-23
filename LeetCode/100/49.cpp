// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>
#include <unordered_map>

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

// space
class Solution {
 public:
  vector<vector<string>> groupAnagrams(vector<string>& strs) {
    vector<vector<string>> res; 
    std::map<string, vector<string>> M; 
    for (auto& str: strs) {
      auto tmp = str; 
      std::sort(tmp.begin(), tmp.end());
      M[tmp].emplace_back(std::move(str)); 
    }
    for (auto& x: M) {
      res.emplace_back(std::move(x.second));
    }
    return res; 
  }
};

// time
class Solution {
 public:
  vector<vector<string>> groupAnagrams(vector<string>& strs) {
    vector<vector<string>> res; 
    std::map<vector<int>, vector<string>> M; 
    for (auto& str: strs) {
      auto tmp = std::vector<int>(26); 
      for (auto c: str) ++tmp[c - 'a']; 
      M[tmp].emplace_back(std::move(str)); 
    }
    for (auto& x: M) {
      res.emplace_back(std::move(x.second));
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