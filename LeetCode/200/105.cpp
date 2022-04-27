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

vector<int> cnt(6000);
int n;
class Solution {
 public:
  TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    n = preorder.size();
    for (int i = 0; i < n; ++i) {
      cnt[inorder[i] + 3000] = i;
    }
    return dfs(preorder, inorder, 0, n - 1, 0, n - 1);
  }

  TreeNode* dfs(vector<int>& preorder,
                vector<int>& inorder,
                int pl,
                int pr,
                int il,
                int ir) {
    if (pl > pr or il > ir)
      return nullptr;
    // cout << pl << " " << pr << " ";
    // cout << il << " " << ir << endl;
    int val = preorder[pl] + 3000;
    return new TreeNode(
        preorder[pl],
        dfs(preorder, inorder, pl + 1, cnt[val] - il + pl, il, cnt[val] - 1),
        dfs(preorder, inorder, cnt[val] - il + pl + 1, pr, cnt[val] + 1, ir));
  }
};