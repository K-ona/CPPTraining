struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode* insertionSortList(ListNode* head) {
    ListNode anchor(-100000);
    while (head) {
      auto next = head->next;
      
      auto tmpa = &anchor; 
      ListNode* pre = nullptr; 
      while (tmpa) {
        if (tmpa->val <= head->val) {
          pre = tmpa; 
          tmpa = tmpa->next; 
        } else break;
      }
      pre->next = head; 
      head->next = tmpa; 
      head = next;
    }
    return anchor.next; 
  }
};