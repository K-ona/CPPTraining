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
    bool isValidBST(TreeNode* root) {
        return dfs(root, INT_MAX + 1ll, INT_MIN - 1ll); 
    }
    bool dfs(TreeNode* root, long long max, long long min) {
        if (!root) return true;
        bool res = true;
        if (root->left) {
            if (root->val <= root->left->val or 
                root->left->val <= min) return false;
            res = res and dfs(root->left, root->val, min); 
        }
        if (root->right) {
            if (root->val >= root->right->val or
                root->right->val >= max) return false;
            res = res and dfs(root->right, max, root->val);
        }
        return res; 
    }
};