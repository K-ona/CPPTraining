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

int n;
int cnt[6005];

class Solution {
 public:
  TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    n = inorder.size();
    for (int i = 0; i < n; ++i) {
      cnt[inorder[i] + 3000] = i;
    }
    return dfs(postorder, inorder, 0, n - 1, 0, n - 1);
  }

  TreeNode* dfs(vector<int>& postorder,
                vector<int>& inorder,
                int pl,
                int pr,
                int il,
                int ir) {
    if (pl > pr or il > ir)
      return nullptr;
    int val = postorder[pr] + 3000;
    return new TreeNode(
        postorder[pr],
        dfs(postorder, inorder, pl, cnt[val] - il + pl - 1, il, cnt[val] - 1),
        dfs(postorder, inorder, cnt[val] - il + pl, pr - 1, cnt[val] + 1, ir));
  }
};