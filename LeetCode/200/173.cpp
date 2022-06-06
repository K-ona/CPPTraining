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
class BSTIterator {
  std::stack<TreeNode*> stk;
  TreeNode* cur;

 public:
  BSTIterator(TreeNode* root) { cur = root; }

  int next() {
    while (cur) {
      stk.push(cur);
      cur = cur->left;
    }
    cur = stk.top();
    stk.pop();
    int res = cur->val;
    cur = cur->right;
    return res;
  }

  bool hasNext() {
    if (!cur and stk.empty())
      return false;
    return true;
  }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */