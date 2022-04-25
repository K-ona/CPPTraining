class Solution {
 public:
  bool isSymmetric(TreeNode* root) {
    std::queue<TreeNode*> Q;
    int len = 2;
    if (!root->left and !root->right) {
      return true;
    } else if (root->left and root->right and root->left->val == root->right->val) {
      Q.push(root->left);
      Q.push(root->right);
      while (!Q.empty()) {
        int tmp = 0;

        vector<std::pair<int, int>> vt;
        vt.reserve(len * 2); 
        if (len & 1) return false; 

        for (int i = 0; i < len / 2; ++i) {
          root = Q.front();
          Q.pop();
          if (root->left) {
            ++tmp;
            Q.push(root->left);
            vt.push_back({root->left->val, i * 2});
          }
          if (root->right) {
            ++tmp;
            Q.push(root->right);
            vt.push_back({root->right->val, i * 2 + 1});
          }
        }

        for (int i = len / 2 - 1; i >= 0; --i) {
          root = Q.front();
          Q.pop();
          if (root->left) {
            ++tmp;
            Q.push(root->left);
            if (vt.empty()) return false; 
            if (vt.back().first != root->left->val or vt.back().second != i * 2 + 1) {
              return false;
            }
            vt.pop_back(); 
          }
          if (root->right) {
            ++tmp;
            Q.push(root->right);
            if (vt.empty()) return false; 
            if (vt.back().first != root->right->val or vt.back().second != i * 2) {
              return false;
            }
            vt.pop_back(); 
          }
        }
        len = tmp; 
      }
    } else {
      return false;
    }

    return true;
  }
};
