/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
 public:
  Node* connect(Node* root) {
    std::queue<Node*> Q;
    auto ans = root; 
    int size = 1;
    if (root)
        Q.push(root);
    while (!Q.empty()) {
      for (int i = 0; i < size; ++i) {
        root = Q.front();
        Q.pop();
        root->next = (i == size - 1) ? nullptr : Q.front();
        if (root->left and root->right) {
          Q.push(root->left);
          Q.push(root->right);
        }
      }
      size *= 2;
    }
    return ans;
  }
};