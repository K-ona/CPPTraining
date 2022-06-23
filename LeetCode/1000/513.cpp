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
  int findBottomLeftValue(TreeNode* root) {
    std::queue<TreeNode*> Q;
    Q.push(root);
    int ans = root->val;
    while (!Q.empty()) {
      ans = Q.front()->val;
      for (int i = Q.size(); i; --i) {
        if (Q.front()->left)
          Q.push(Q.front()->left);
        if (Q.front()->right)
          Q.push(Q.front()->right);
        Q.pop();
      }
    }
    return ans;
  }
};