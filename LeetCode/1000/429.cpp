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

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
 public:
  vector<vector<int>> levelOrder(Node* root) {
    if (!root)
      return {};
    vector<vector<int>> res;
    res.reserve(1000);
    queue<Node*> q;
    q.push(root);
    int width = 1;
    while (!q.empty()) {
      vector<int> tmp;
      int tmpw = 0;
      for (int i = 0; i < width; ++i) {
        Node* cur = q.front();
        q.pop();
        tmp.push_back(cur->val);
        for (auto& child : cur->children) {
          if (child) {
            q.push(child);
            tmpw++;
          }
        }
      }
      width = tmpw;
      res.push_back(std::move(tmp));
    }
    return res;
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