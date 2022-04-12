/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
      auto dummy = new ListNode;
      auto ans = dummy; 
      ListNode* pre = nullptr; 
      ListNode* sep = nullptr; 
      while (head) {
        if (head->val < x) {
            dummy->next = head; 
            dummy = dummy->next;
            if (pre) pre->next = head->next;
            head = head->next; 
        } else {
            if (!sep) sep = head; 
            pre = head; 
            head = head->next;
        }
      }
      dummy->next = sep; 
      return ans->next; 
    }
};