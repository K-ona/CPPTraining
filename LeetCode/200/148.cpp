#include <bits/stdc++.h>

using namespace std; 

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
  tuple<ListNode*, ListNode*> partition(ListNode* begin, ListNode* end) {
    int sep = begin->val; 
    ListNode* res = begin; 
    ListNode* head = begin; 
    ListNode* tail = begin; 

    while (begin != end) {
    //   cout << begin->val << " "; 
      auto next = begin->next; 
      if (begin->val <= sep) {
        begin->next = head; 
        head = begin; 
      } else {
        begin->next = nullptr; 
        tail->next = begin; 
        tail = begin; 
      }
      begin = next; 
    }
    // cout << endl; 
    tail->next = end; 
    return {res, head};
  }
 
  tuple<ListNode*, ListNode*> quick_sort(ListNode* begin, ListNode* end) {
    if (begin->next == end) return {begin, begin}; 
    
    auto [sep, head] = partition(begin, end); 
    if (sep == head) {
      auto [h, t] = quick_sort(sep->next, end);
      sep->next = h; 
      return {sep, t}; 
    }

    auto [h1, t1] = quick_sort(head, sep); 
    if (sep->next != end) {
      auto [h2, t2] = quick_sort(sep->next, end); 
      t1->next = sep; 
      sep->next = h2; 
      return {h1, t2}; 
    } else {
      t1->next = sep; 
      return {h1, sep}; 
    }
  }

 public:
  ListNode* sortList(ListNode* head) {
    if (head)
        return std::get<0>(quick_sort(head, nullptr)); 
    return nullptr;
  }
};


class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;
        auto slow = head, fast = head;
        while (fast->next && fast->next->next)
            slow = slow->next, fast = fast->next->next;
        // 切链
        fast = slow->next, slow->next = nullptr;
        return merge(sortList(head), sortList(fast));
    }

private:
    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode sub(0), *ptr = &sub;
        while (l1 && l2) {
            auto &node = l1->val < l2->val ? l1 : l2;
            ptr = ptr->next = node, node = node->next;
        }
        ptr->next = l1 ? l1 : l2;
        return sub.next;
    }
};


int main() {
  ListNode e(0);
  ListNode d(4, &e);
  ListNode c(3, &d);
  ListNode b(5, &c);
  ListNode a(-1, &b); 
  Solution().sortList(&a); 

}