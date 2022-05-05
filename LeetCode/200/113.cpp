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

vector<int> stk;
int tar;
class Solution {
 public:
  vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
    if (!root)
      return {};
    vector<vector<int>> res;
    stk.clear();
    tar = targetSum;
    stk.push_back(root->val);
    dfs(root, root->val, stk, res);
    return res;
  }

  void dfs(TreeNode* root,
           int sum,
           vector<int>& stk,
           vector<vector<int>>& res) {
    if (!root->left and !root->right) {
      if (sum == tar)
        res.emplace_back(stk);
    }
    if (root->left)
      stk.push_back(root->left->val),
          dfs(root->left, sum + root->left->val, stk, res), stk.pop_back();
    if (root->right)
      stk.push_back(root->right->val),
          dfs(root->right, sum + root->right->val, stk, res), stk.pop_back();
  }
};
