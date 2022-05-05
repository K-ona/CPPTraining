/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
 public:
  vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
    vector<int> res1, res2;
    res1.reserve(5000);
    res2.reserve(5000);
    dfs(root1, res1);
    dfs(root2, res2);
    return Merge(res1, res2);
  }

  void dfs(TreeNode* root, vector<int>& res) {
    if (!root)
      return;
    if (root->left)
      dfs(root->left, res);
    res.push_back(root->val);
    if (root->right)
      dfs(root->right, res);
  }

  vector<int> Merge(vector<int>& first, vector<int> second) {
    vector<int> res;
    int n = first.size();
    int m = second.size();
    res.reserve(n + m);
    int i, j;
    for (i = 0, j = 0; i < n and j < m;) {
      if (first[i] < second[j])
        res.push_back(first[i++]);
      else
        res.push_back(second[j++]);
    }
    while (i < n) {
      res.push_back(first[i++]);
    }
    while (j < m) {
      res.push_back(second[j++]);
    }
    return res;
  }
};