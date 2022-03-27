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
  vector<int> missingRolls(vector<int>& rolls, int mean, int n) {
    int sum = 0;  
    for (auto x: rolls) {
      sum += x;
    }
    sum = mean * (n + rolls.size()) - sum;

    if (sum < n or sum > 6 * n) return {}; 
    int val = sum / n; 
    sum %= n;
    vector<int> ans(n, val); 
    for (int i = 0; i < sum; ++i) {
      ++ans[i];
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