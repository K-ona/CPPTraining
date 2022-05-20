struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

#include <stack>
#include <vector>

class Solution {
 public:
  std::vector<int> preorderTraversal(TreeNode* root) {
    std::vector<int> res;
    res.reserve(100);
    std::stack<TreeNode*> stk;
    stk.push(root);
    while (!stk.empty()) {
      auto root = stk.top();
      stk.pop(); 
      while (root) {
        if (root->right) stk.push(root->right); 
        res.push_back(root->val); 
        root = root->left; 
      }
    }
    return res; 
  }
};