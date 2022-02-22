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
    int romanToInt(string s) {
      int res = 0; 
      int len = s.size(); 
      std::unordered_map<char, int> M; 
      M['I'] = 1; 
      M['V'] = 5; 
      M['X'] = 10; 
      M['L'] = 50; 
      M['C'] = 100; 
      for (int i = 0; i < len; ++i) {
        if (i + 1 < len)
      }
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