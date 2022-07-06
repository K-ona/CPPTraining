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
    int k; 
public:
    int kthSmallest(TreeNode* root, int k) {
        std::priority_queue<int> PQ; 
        this->k = k; 
        DFS(root, PQ); 
        return PQ.top(); 
    }

    void DFS(TreeNode* root, std::priority_queue<int>& PQ) {
        if (!root) return ; 
        if (PQ.size() < k) PQ.push(root->val); 
        else if (PQ.top() > root->val) PQ.pop(), PQ.push(root->val); 
        DFS(root->left, PQ);
        DFS(root->right, PQ);
    }
};