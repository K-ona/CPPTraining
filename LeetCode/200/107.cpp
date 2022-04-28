/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        if (!root)
        return {};
        std::queue<TreeNode*> Q;
        std::vector<std::vector<int>> res;
        res.reserve(2000); 
        Q.push(root);
        res.emplace_back(std::vector<int>{root->val});
        int len = 1;
        while (!Q.empty()) {
        std::vector<int> tmp;
        tmp.reserve(len * 2);
        int cnt = 0;
        while (len--) {
            root = Q.front();
            Q.pop();
            if (root->left) {
            tmp.push_back(root->left->val);
            Q.push(root->left);
            cnt++;
            }
            if (root->right) {
            tmp.push_back(root->right->val);
            Q.push(root->right);
            cnt++;
            }
        }
        len = cnt;
        if (len)
            res.emplace_back(std::move(tmp));
        }
        std::reverse(res.begin(), res.end());
        return res;
  }
};