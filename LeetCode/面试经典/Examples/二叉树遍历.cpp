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
        if (root->right)
          stk.push(root->right);
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
        root = stk.top();
        stk.pop();
        res.push_back(root->val);
        root = root->right;
      }
    }
    return res;
  }
};

// 后序遍历

class Solution {
  void find(std::stack<TreeNode*>& stk) {
    while (auto cur = stk.top()) {
      if (cur->left) {
        if (cur->right) stk.push(cur->right); 
        stk.push(cur->left); 
      } else {
        stk.push(cur->right); 
      }
    }
    stk.pop(); // 栈顶为空时 while 循环结束，弹出空节点
  }

 public:
  std::vector<int> postorderTraversal(TreeNode* root) {
    std::stack<TreeNode*> stk;
    std::vector<int> res;
    res.reserve(100);

    if (root) stk.push(root); 
    while (!stk.empty()) {
      if (stk.size() and ((stk.top()->left == root and !stk.top()->right) or (stk.top()->right == root))) {
      } else {
        find(stk); 
      }
      root = stk.top(); 
      stk.pop(); 
      res.push_back(root->val); 
    }
    return res;
  }
};