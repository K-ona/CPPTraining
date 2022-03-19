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

struct TreeNode
{
  int val;
  TreeNode* left;
  TreeNode* right; 
  TreeNode(): val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
};

class Solution {
 public:
  string tree2str(TreeNode* root) {
    string res;
    res.reserve(30000); 
    DFS(root, res); 
    return res; 
  }

  void DFS(TreeNode* root, string& s) {
    s += std::to_string(root->val);  

    if (!root->left and !root->right) return;

    s += '('; 
    if (root->left) DFS(root->left, s); 
    s += ')'; 

    if (root->right) {
      s += '('; 
      DFS(root->right, s); 
      s += ')'; 
    }
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