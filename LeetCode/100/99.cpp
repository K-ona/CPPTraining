// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>

#include <string.h>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::queue;
using std::string;
using std::vector;

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
  void recoverTree(TreeNode* root) { dfs(root, nullptr, nullptr); }

  bool dfs(TreeNode* root, TreeNode* max, TreeNode* min) {
    if (root->left) {
      if (root->val <= root->left->val) {
        std::swap(root->val, root->left->val);
        return true;
      }
      if (min)
      if (root->left->val <= min->val) {
        std::swap(root->left->val, min->val);
        return true;
      }
      if (dfs(root->left, root, min))
        return true;
    }

    if (root->right) {
      if (root->val >= root->right->val) {
        std::swap(root->val, root->right->val);
        return true;
      }
      if (max)
      if (root->right->val >= max->val) {
        std::swap(root->right->val, max->val);
        return true;
      }
      if (dfs(root->right, max, root))
        return true;
    }
    return false;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  return 0;
}