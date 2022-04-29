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
    int minDepth(TreeNode* root) {
        if (!root) return 0;
        return 1 + dfs(root); 
    }

    int dfs(TreeNode* root) {
        if (!root) return 100000; 
        if (!root->left and !root->right) return 0;
        return min(dfs(root->left), dfs(root->right)) + 1; 
    }
};