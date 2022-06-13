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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res; 
        res.reserve(100); 
        if (root)
          bfs(res, root);
        return res; 
    }

    void bfs(vector<int>& res, TreeNode* root) {
        std::queue<TreeNode*> Q;
        Q.push(root);
        int val = root->val; 
        while (!Q.empty()) {
            res.push_back(val); 
            for (int sz = Q.size(); sz--; ) {
                auto root = Q.front(); Q.pop(); 
                if (root->left)  { Q.push(root->left);  val = root->left->val; }; 
                if (root->right) { Q.push(root->right); val = root->right->val; }; 
            }
        }
    }
};