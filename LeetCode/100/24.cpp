struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
 public:
  ListNode* swapPairs(ListNode* head) {
    ListNode* ptr = new ListNode; 
    ptr->next = head; 
    auto res = ptr; 
    while (ptr) {
      ptr = swap(ptr); 
    }
    return res ? res->next : nullptr; 
  }

  ListNode* swap(ListNode* pre) {
    if (!pre->next or !pre->next->next) return nullptr; 
    ListNode* cur = pre->next; 
    pre->next = cur->next; 
    cur->next = cur->next->next; 
    pre->next->next = cur; 
    return cur; 
  }

};