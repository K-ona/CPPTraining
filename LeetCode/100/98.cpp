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
  TreeNode* first;
  TreeNode* second;

 public:
  void recoverTree(TreeNode* root) {
    first = second = nullptr;
    auto suc = dfs(root, nullptr);
    std::swap(second->val, first->val);
  }

  TreeNode* dfs(TreeNode* root, TreeNode* pre) {
    if (root->left)
      pre = dfs(root->left, pre);
    if (pre and pre->val >= root->val) {
      if (!first) {
        first = pre;
        second = root;
      } else
        second = root;
    }
    if (root->right) {
      return dfs(root->right, root);
    }
    return root;
  }
};