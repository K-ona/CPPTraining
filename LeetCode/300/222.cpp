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
    int h; 
    bool flag = false; 
    int ans; 
public:
    int countNodes(TreeNode* root) {
        h = -1; 
        auto rt = root; 
        while (rt) {
            rt = rt->left;
            ++h;
        }
        if (!~h) return 0; 
        dfs(root, 0, 1); 
        return ans; 
    }
    void dfs(TreeNode* root, int h, int num) {
        if (flag) return ; 
        if (h == this->h) ans = num, flag = true; 
        if (root->right)
            dfs(root->right, h + 1, num * 2 + 1);
        if (root->left)
            dfs(root->left, h + 1, num * 2);
    }
    
};