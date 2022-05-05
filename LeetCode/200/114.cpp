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
  void flatten(TreeNode* root) {
    if (!root)
      return;
    TreeNode x;
    dfs(root, &x);
  }

  TreeNode* dfs(TreeNode* root, TreeNode* pre) {
    auto tmpl = root->left;
    auto tmpr = root->right;

    pre->left = nullptr, pre->right = root;

    pre = root;
    if (tmpl)
      pre = dfs(tmpl, pre);

    if (tmpr)
      return dfs(tmpr, pre);

    return pre;
  }
};