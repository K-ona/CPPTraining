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

int value; 
class Solution {
public:
    bool isUnivalTree(TreeNode* root) {
        if (!root) return true; 
        value = root->val; 
        return dfs(root);
    }
    
    bool dfs(TreeNode* root) {
        if (!root) return true; 
        if (root->val != value) return false;
        bool res = true; 
        res and_eq dfs(root->left); 
        if (res)
            res and_eq dfs(root->right); 
        return res;
    }
};