// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
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
};

class Solution {
    int vis[20005];
    int cnt = 0; 
 public:
  bool findTarget(TreeNode* root, int k) {
    memset(vis, 0, sizeof vis); 
    traverse(root); 

    if (cnt < 2) return false; 
    for (int i = 0; i < 20001; ++i) {
      if (i == k + 20000 - i) {
        if (vis[i] >= 2) 
        return true;
      }
      else if (vis[i] and (k + 20000 - i) < 20005 and vis[k + 20000 - i]) {
          return true; 
      }
    }
    return false; 
  }

  void traverse(TreeNode* root) {
    if (!root) return ; 
    ++cnt; 
    // cout << root->val + 10000 << endl; 
    ++vis[root->val + 10000]; 
    traverse(root->left); 
    traverse(root->right); 
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