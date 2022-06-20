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
  ListNode* removeElements(ListNode* head, int val) {
    while (head && head->val == val)
      head = head->next;
    if (!head)
      return nullptr;
    auto res = head;
    while (head->next) {
      auto next = head->next;
      if (next->val == val) {
        head->next = next->next;
        continue;
      }
      head = next;
    }
    return res;
  }
};