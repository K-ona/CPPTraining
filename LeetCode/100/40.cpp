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

int stk[105]; 
int presum[105]; 
int top; 
class Solution {
  int n;
  vector<vector<int>> res; 
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    std::sort(candidates.begin(), candidates.end()); 
    n = candidates.size(); 
    presum[0] = candidates[0]; 
    for (int i = 1; i < n; ++i) {
      presum[i] = presum[i - 1] + candidates[i]; 
    }
    DFS(candidates, 0, target, 0); 
    std::sort(res.begin(), res.end()); 
    res.resize(std::unique(res.begin(), res.end()) - res.begin()); 
    return res; 
  }

  void DFS(vector<int>& candidates, int pos, int target, int top) {
    if (!target) {
      res.push_back(vector<int>(stk, stk + top)); 
      return ;
    }
    for (int i = pos; i < n; ++i) {
      int cnt = target / candidates[i]; 
    //   cout << i << endl; 
      while (i + cnt < n and candidates[i + cnt] == candidates[i]) { ++i; }
    //   --i; 

      if (i < n and target - candidates[i] >= 0 and presum[n - 1] - presum[i] >= target - candidates[i]) {
        // cout << i << " " << target << endl; 
        stk[top] = candidates[i]; 
        DFS(candidates, i + 1, target - candidates[i], top + 1); 
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