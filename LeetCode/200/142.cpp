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
    ListNode *detectCycle(ListNode *head) {
        auto fast = head, slow = head; 
        while (fast and slow) {
            slow = slow->next; 
            if (!fast->next) return nullptr;
            fast = fast->next->next;
            if (slow == fast) {
                auto res = head; 
                while (res != slow) {
                    res = res->next; 
                    slow = slow->next; 
                }
                return res; 
            }
        }
        return nullptr;
    }
};