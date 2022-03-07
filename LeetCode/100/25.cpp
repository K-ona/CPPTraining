struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
 public:
  ListNode* reverseKGroup(ListNode* head, int k) {
    int cnt = 0; 
    static ListNode* res = new ListNode(); 
    res->next = head; 
    ListNode* begin = res; 
    while (head) {
      if (++cnt == k) {
        auto tmp1 = head->next; 
        auto tmp2 = begin->next; 
        begin->next = swap_k(begin->next, head); 
        begin = tmp2; 
        cnt = 0; 
        head = tmp1; 
      } else {
        head = head->next; 
      }
    }
    return res->next; 
  }

  ListNode* swap_k(ListNode* begin, ListNode* end) { 
    auto pre = end->next; 
    while (begin != end) { 
      auto tmp = begin->next; 
      begin->next = pre; 
      pre = begin; 
      begin = tmp; 
    } 
    end->next = pre; 
    return end; 
  } 

};