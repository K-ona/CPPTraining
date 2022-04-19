struct TreeNode
{
  int val;
  TreeNode* left;
  TreeNode* right; 
  TreeNode(): val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}

};

#include <vector>

class Solution {
 public:
  std::vector<TreeNode*> generateTrees(int n) {
    if (!n) return {}; 
    return DFS(1, n);
  }

  std::vector<TreeNode*> DFS(int left, int right) {
    if (left == right) return {new TreeNode(left)}; 
    if (left > right) return { nullptr };

    std::vector<TreeNode*> res; 
    res.reserve(16);
    for (int i = left; i <= right; ++i) {
      auto leftroot = DFS(left, i - 1); 
      auto rightroot = DFS(i + 1, right); 
      for (auto& l: leftroot) {
        for (auto& r: rightroot) {
          res.emplace_back( new TreeNode(i, l, r) ); 
        }
      }
    }
    return res; 
  }
};