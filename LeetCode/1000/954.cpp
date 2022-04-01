// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
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

class Solution {
 public:
  bool canReorderDoubled(vector<int>& arr) {
    std::map<int, int> M; 
    for (auto elem : arr) {
      ++M[elem];
    }
  
    for (auto it = M.begin(); it != M.end(); ++it) {
      if (it->second == 0) continue;
      if (it->first == 0) {
        if (M[it->first] & 1)
          return false; 
      }
      else if (it->first > 0) {
        if (M[it->first * 2] >= it->second) {
          M[it->first * 2] -= it->second; 
        } else return false;
        
      } else {
        if (it->first % 2 != 0) return false;
        if (M[it->first / 2] >= it->second) {
          M[it->first / 2] -= it->second; 
        } else return false;
      }
    }
    return true; 
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