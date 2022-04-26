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
int max = 0;
class Solution {
 public:
  int maxDepth(TreeNode* root) {
    if (!root)
      return 0;
    ::max = 0;
    vector<std::pair<TreeNode*, int>> stk;
    stk.reserve(10005);
    stk.emplace_back(std::make_pair(root, 1));
    while (!stk.empty()) {
      auto root = stk.back();
      stk.pop_back();
      ::max = std::max(::max, root.second);
      if (root.first->left) {
        stk.emplace_back(std::make_pair(root.first->left, root.second + 1));
      }
      if (root.first->right) {
        stk.emplace_back(std::make_pair(root.first->right, root.second + 1));
      }
    }
    return ::max;
  }
};