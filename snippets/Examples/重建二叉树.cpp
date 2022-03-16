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

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
  std::unordered_map<int, int> M; 
 public:
  /**
   * @param preorder: preorder of the tree
   * @param inorder: inorder of the tree
   * @return: the tree's root node after the tree built
   */
  TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    if (preorder.empty()) return nullptr; 
    int n = preorder.size(); 
    for (int i = 0; i < n; ++i) {
      M[inorder[i]] = i; 
    }
    return build(preorder, 0, inorder, 0, n);
  }

  TreeNode* build(vector<int>& preorder, int lp, vector<int>& inorder, int l, int r) {
    if (preorder.size() <= lp or l == r) return nullptr; 
    TreeNode* root = new TreeNode(preorder[lp]); 
    int i = M[preorder[lp]]; 
    root->left = build(preorder, lp + 1, inorder, l, i); 
    root->right = build(preorder, lp + i - l + 1, inorder, i + 1, r); 
    return root; 
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