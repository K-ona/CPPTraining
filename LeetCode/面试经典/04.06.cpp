/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
TreeNode* ans;
TreeNode* p;
class Solution {
 public:
  TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
    ::p = p;
    ans = nullptr;
    dfs(root, nullptr);
    return ans;
  }

  TreeNode* dfs(TreeNode* root, TreeNode* pre) {
    TreeNode* last = root;
    if (root->left)
      pre = dfs(root->left, pre);
    if (pre == p)
      ans = root;
    if (root->right)
      last = dfs(root->right, root);
    return last;
  }
};