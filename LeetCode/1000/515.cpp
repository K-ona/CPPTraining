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
  vector<int> largestValues(TreeNode* root) {
    std::queue<TreeNode*> Q;
    if (root)
      Q.push(root);
    vector<int> res;
    res.reserve(1024);
    while (!Q.empty()) {
      int max = INT32_MIN;
      for (int i = Q.size(); i; --i) {
        auto root = Q.front();
        if (root->val > max)
          max = root->val;
        if (root->left)
          Q.push(root->left);
        if (root->right)
          Q.push(root->right);
        Q.pop();
      }
      res.push_back(max);
    }
    return res;
  }
};