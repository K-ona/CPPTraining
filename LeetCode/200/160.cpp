/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
 public:
  ListNode* getIntersectionNode(ListNode* A, ListNode* B) {
    auto headA = A, headB = B;
    while (true) {
      if (headA == headB)
        return headA;
      if (headA)
        headA = headA->next;
      else
        headA = B;
      if (headB)
        headB = headB->next;
      else
        headB = A;
    }
    return nullptr;
  }
};