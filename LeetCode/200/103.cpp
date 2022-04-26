/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
 public:
  vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    if (!root)
      return {};
    vector<vector<int>> res;
    res.reserve(256);
    bfs(res, root);
    return res;
  }

  void bfs(vector<vector<int>>& res, TreeNode* root) {
    std::queue<TreeNode*> Q;
    Q.push(root);
    bool flag = true;
    int cnt = 1;
    res.push_back({root->val});
    while (!Q.empty()) {
      int tmp = 0;
      vector<int> vt;
      vt.reserve(cnt * 2);
      for (int i = 0; i < cnt; ++i) {
        root = Q.front();
        Q.pop();
        if (root->left) {
          Q.push(root->left);
          vt.push_back(root->left->val);
          ++tmp;
        }
        if (root->right) {
          Q.push(root->right);
          vt.push_back(root->right->val);
          ++tmp;
        }
      }
      if (!vt.empty()) {
        if (flag)
          std::reverse(vt.begin(), vt.end());
        res.push_back(std::move(vt));
      }
      flag ^= true;
      cnt = tmp;
    }
  }
};