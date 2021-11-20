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

#include <unordered_map>
#include <unordered_set>

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        std::unordered_set<int> dp; 
        for (auto &x: nums) {
            dp.insert(x); 
        }

        int res = 0; 
        for (auto x: dp) {
          cout << x << endl; 
          int cnt = 1; 
          if (dp.count(x - 1)) continue; 
          while(dp.count(x + 1)) {
            ++x; 
            ++cnt; 
          }
          res = std::max(res, cnt); 
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

  Solution app; 
  vector<int> a{3, 1, 2, 4, 5}; 
  cout << app.longestConsecutive(a) << endl; 

  return 0;
}