struct ListNode {
  ListNode* next;
};

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
      ListNode* res = new ListNode(); 
      res->next = head; 
      ListNode* right_node = res;
      ListNode* left_node = res;
      int sep = right - left; 
      for (int i = 0; i < sep; ++i) {
        right_node = right_node->next; 
      }
      ListNode* pre = nullptr; 
      for (int i = 0; i < left; ++i) {
        pre = left_node; 
        right_node = right_node->next; 
        left_node = left_node->next;
      }
      pre->next = right_node; 
      pre = right_node->next; 
      for (int i = 0; i <= sep; ++i) {
          auto tmp = left_node->next; 
          left_node->next = pre; 
          pre = left_node; 
          left_node = tmp; 
      }
      return res->next; 
    }
};