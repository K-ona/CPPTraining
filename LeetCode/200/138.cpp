class Solution {
 public:
  Node* copyRandomList(Node* head) {
    if (!head) return nullptr;

    std::unordered_map<Node*, Node*> M;
    auto tmp = head; 
    while (tmp) {
      M[tmp] = new Node(tmp->val); 
      tmp = tmp->next; 
    }
    tmp = head; 
    while (tmp) {
      M[tmp]->next = M[tmp->next]; 
      M[tmp]->random = M[tmp->random];
      tmp = tmp->next; 
    }
    return M[head];
  }
};