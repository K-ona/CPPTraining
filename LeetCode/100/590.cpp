#include <stack>
#include <unordered_map>
#include <vector>

using std::vector;

class Node {
 public:
  int val;
  vector<Node*> children;

  Node() {}

  Node(int _val) { val = _val; }

  Node(int _val, vector<Node*> _children) {
    val = _val;
    children = _children;
  }
};

class Solution {
 public:
  vector<int> postorder(Node* root) {
    vector<int> res;
    // traversal(root, res);
    use_stack(root, res);
    return res;
  }

  void traversal(Node* root, vector<int>& res) {
    if (!root)
      return;
    for (auto x : root->children)
      traversal(x, res);
    res.push_back(root->val);
  }

  void use_stack(Node* root, vector<int>& res) {
    if (!root)
      return;
    std::stack<Node*> S;
    std::unordered_map<Node*, int> cnt;
    S.push(root);
    while (!S.empty()) {
      auto root = S.top();
      if (root->children.empty() or cnt[root]) {
        res.emplace_back(root->val);
        S.pop();
        continue;
      }
      for (auto it = root->children.rbegin(); it != root->children.rend();
           ++it) {
        S.emplace(*it);
      }
      ++cnt[root];
    }
  }
};