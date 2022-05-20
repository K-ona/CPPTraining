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

// 前序遍历
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

// 中序遍历
class Solution {
 public:
  std::vector<int> inorderTraversal(TreeNode* root) {
    std::stack<TreeNode*> stk;
    std::vector<int> res; 
    res.reserve(100);
    
    while (root or !stk.empty()) {
      if (root) {
        stk.push(root); 
        root = root->left; 
      } else {
        root = stk.top(); stk.pop(); 
        res.push_back(root->val); 
        root = root->right;
      } 
    }
    return res;
  }
};

// 后序遍历

class Solution {
public:
    std::vector<int> postorderTraversal(TreeNode* root) {
        std::vector<int> res;
        res.reserve(100); 


        return res; 
    }
}; 