struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
 public:
  void reorderList(ListNode* head) { 
    auto mid = get_mid(head); 
    auto begin = reverse(mid->next);
    merge(head, begin); 
  }

  ListNode* get_mid(ListNode* head) {
    if (!head) return nullptr; 
    auto slow = head, fast = head; 
    while (fast->next && fast->next->next) {
      slow = slow->next; 
      fast = fast->next->next; 
    }
    return slow; 
  }

  ListNode* reverse(ListNode* begin, ListNode* end = nullptr, ListNode* pre = nullptr) {
    while (begin != end) {
      auto tmp = begin->next; 
      begin->next = pre; 
      pre = begin; 
      begin = tmp; 
    }
    return pre; 
  }

  void merge(ListNode* first, ListNode* second) {
    while (first and second) {
      auto ft = first->next; 
      auto st = second->next; 
     
      first->next = second; 
      second->next = ft; 

      first = ft; 
      second = st; 
    }
    first->next = nullptr; 
  }
};