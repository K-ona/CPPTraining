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

bool ans;
int tar; 
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        ans = false; 
        tar = targetSum; 
        if (!root) return false; 
        dfs(root, root->val); 
        return ans; 
    }
    void dfs(TreeNode* root, int sum) {
        if (!root->left and !root->right) {
            if (sum == tar) 
                ans = true; 
        }
        if (root->left)
            dfs(root->left, sum + root->left->val);
        if (root->right)
            dfs(root->right, sum + root->right->val);
    }
};