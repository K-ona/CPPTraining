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
    int lengthOfLongestSubstring(string s) {
      int vis[256];  
      memset(vis, -1, sizeof(vis)); 
      int len = static_cast<int>(s.size()); 
      int ans = 0; 
      for (int l = 0, r = 0; r < len; ++r) {
        if (vis[s[r]] >= l) {
            l = vis[s[r]] + 1; 
        }
        vis[s[r]] = r; 
        ans = std::max(ans, r - l + 1); 
      }
      return ans; 
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