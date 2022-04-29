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
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        return dfs(head, nullptr); 
    }
    TreeNode* dfs(ListNode* head, ListNode* last) {
        if (head == last) return nullptr; 
        ListNode* fast = head, *slow = head;
        while (fast != last) {
            fast = fast->next; 
            if (fast and fast != last) fast = fast->next; 
            else break;
            slow = slow->next; 
        }
        return new TreeNode(slow->val,
                            dfs(head, slow),
                            dfs(slow->next, last));
    }
};