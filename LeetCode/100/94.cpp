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
struct TreeNode;

#include <stack>
#include <vector>

// v1
class Solution {
 public:
  std::vector<int> inorderTraversal(TreeNode* root) {
    std::stack<TreeNode*> stk;
    std::vector<int> res; 
    while (true) {
      find_left(stk, root); 
      if (stk.empty()) break;
      root = stk.top(); stk.pop(); 
      res.push_back(root->val); 
      root =  root->right;
    }
    return res;
  }
  
  void find_left(std::stack<TreeNode*>& stk, TreeNode* root) {
      while (root) {
          stk.push(root); 
          root = root->left; 
      }
  }
};

// v2
class Solution {
 public:
  std::vector<int> inorderTraversal(TreeNode* root) {
    std::stack<TreeNode*> stk;
    std::vector<int> res; 
    
    while (true) {
      if (root) {
        stk.push(root); 
        root = root->left; 
      } else if (!stk.empty()) {
        root = stk.top(); stk.pop(); 
        res.push_back(root->val); 
        root = root->right;
      } else {
        break; 
      }
    }
    return res;
  }
  
};
