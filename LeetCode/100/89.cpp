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
  vector<int> grayCode(int n) {
    vector<int> ans; 
    ans.reserve(1 << n); 
    DFS(0, n, true, ans); 
    return ans;
  }

  void DFS(int res, int rem_bit, bool order, vector<int>& ans) {
    if (!rem_bit) {
      ans.push_back(res); 
      return ;
    }
    if (order) DFS(res << 1 | 0, rem_bit - 1, order, ans), DFS(res << 1 | 1, rem_bit - 1, order ^ true, ans); 
    else DFS(res << 1 | 1, rem_bit - 1, order ^ true, ans), DFS(res << 1 | 0, rem_bit - 1, order, ans); 
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