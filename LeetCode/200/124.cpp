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
int ans; 
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        ans = root->val; 
        dfs(root); 
        return ans; 
    }

    int dfs(TreeNode* root) {
        if (!root) return 0; 
        int left = dfs(root->left); 
        int right = dfs(root->right); 
        int res = std::max(std::max(root->val, root->val + left), root->val + right);
        // cout << root->val << " " << ans << " res = " << res << endl; 
        ans = std::max(std::max(ans, res), root->val + left + right); 
        return res; 
    }
};