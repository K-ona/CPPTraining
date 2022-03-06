#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
  int n;

 public:
  ListNode* mergeKLists(vector<ListNode*>& lists) {
    return DFS(lists, 0, lists.size() - 1);
  }

  ListNode* DFS(vector<ListNode*>& lists, int l, int r) {
    // cout << "l == " << l << " r == " << r << endl;
    if (l > r)
      return nullptr;
    if (l == r)
      return lists[l];
    return mergeTwoLists(DFS(lists, l, (l + r) >> 1),
                         DFS(lists, ((l + r) >> 1) + 1, r));
  }

  ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode* head = new ListNode;
    ListNode* tmp = head;
    while (list1 and list2) {
      if (list1->val < list2->val) {
        head->next = list1;
        list1 = list1->next;
      } else {
        head->next = list2;
        list2 = list2->next;
      }
      head = head->next;
    }
    while (list1) {
      head->next = list1;
      list1 = list1->next;
      head = head->next;
    }
    while (list2) {
      head->next = list2;
      list2 = list2->next;
      head = head->next;
    }
    return tmp->next;
  }
};