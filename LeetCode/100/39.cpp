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

int stk[35]; 
int top; 
class Solution {
  int n;
  vector<vector<int>> res; 
 public:
  vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    n = candidates.size(); 
    DFS(candidates, 0, target, 0); 
    return res; 
  }

  void DFS(vector<int>& candidates, int pos, int target, int top) {
    // cout << pos << endl; 
    if (!target) {
      res.push_back(vector<int>(stk, stk + top)); 
      return ;
    }
    for (int i = pos; i < n; ++i) {
      if (target - candidates[i] >= 0) {
        // cout << i << " " << target << endl; 
        stk[top] = candidates[i]; 
        DFS(candidates, i, target - candidates[i], top + 1); 
      }
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