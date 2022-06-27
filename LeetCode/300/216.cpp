class Solution {
 public:
  vector<vector<int>> combinationSum3(int k, int n) {
    vector<vector<int>> res;
    res.reserve(128);
    vector<int> stk;
    stk.reserve(16);
    DFS(res, 1, k, n, stk);
    return res;
  }

  void DFS(vector<vector<int>>& res, int l, int k, int n, vector<int>& stk) {
    if (k == 0 || l > 9 || n <= 0) {
      if (0 == n && k == 0)
        res.push_back(stk);
      return;
    }
    stk.push_back(l);
    DFS(res, l + 1, k - 1, n - l, stk);
    stk.pop_back();
    DFS(res, l + 1, k, n, stk);
  }
};