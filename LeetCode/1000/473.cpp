#include <algorithm>
#include <vector>
#include <string.h>

using std::vector;

int n;
int len; 
int memo[1 << 15]; 

class Solution {
 public:
  bool makesquare(vector<int>& matchsticks) {
    int sum = 0; 
    for (auto x: matchsticks) sum += x; 
    if (sum % 4) return false; 
    len = sum / 4; 
    n = matchsticks.size(); 
    memset(memo, -1, sizeof(memo));
    return dfs(matchsticks, 0, 0, 0); 
  }

  bool dfs(vector<int>& matchsticks, int cnt, int val, int bitv) {
    // cout << cnt << " " << val << " " << bitv << endl; 
    if (!memo[bitv]) return memo[bitv]; 
    if (bitv == ((1 << n) - 1))
      return true; 
    for (int i = 0; i < n; ++i) {
    //   cout << bitv << " " << (1 << i) << " " << (bitv & (1 << i)) << endl;
      if (!(bitv & (1 << i))) {
        if (val + matchsticks[i] < len) {
          if (dfs(matchsticks, cnt, val + matchsticks[i], bitv | (1 << i)))
            return true;
        }
        if (val + matchsticks[i] == len) {
          if (dfs(matchsticks, cnt + 1, 0, bitv | (1 << i)))
            return true; 
        }
      }
    }
    return memo[bitv] = 0; 
  }
};

int main() {
  return 0;
}