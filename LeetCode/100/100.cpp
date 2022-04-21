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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (bool(p) + bool(q) == 1) return false; 
        if (bool(p) + bool(q) == 0) return true; 
        return dfs(p, q); 
    }   

    bool dfs(TreeNode* p, TreeNode* q) {
        if (q->val != p->val) return false; 

        bool res = true;
        if ((bool)q->left + (bool)p->left == 1) return false; 
        if (q->left)
        res = res && dfs(q->left, p->left);  

        if ((bool)q->right + (bool)p->right == 1) return false; 
        if (q->right)
        res = res && dfs(q->right, p->right);  
        return res; 
    }
};