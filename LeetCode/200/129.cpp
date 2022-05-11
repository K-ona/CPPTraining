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
    int sumNumbers(TreeNode* root) {
        return dfs(root, root->val);
    }
    int dfs(TreeNode* root, int sum) {
        if (!root->left and !root->right) return sum; 
        int res = 0;
        if (root->left)
            res += dfs(root->left, sum * 10 + root->left->val); 
        if (root->right)
            res += dfs(root->right, sum * 10 + root->right->val); 
        return res;
    }
};