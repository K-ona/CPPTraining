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
int ans;
class Solution {
 public:
  int sumRootToLeaf(TreeNode* root) {
    ans = 0;
    if (root)
      dfs(root, 0);
    return ans;
  }

  void dfs(TreeNode* root, int curnum) {
    curnum = (curnum << 1) | root->val;
    if (!root->left and !root->right) {
      ans += curnum;
      return;
    }
    if (root->left)
      dfs(root->left, curnum);
    if (root->right)
      dfs(root->right, curnum);
  }
};