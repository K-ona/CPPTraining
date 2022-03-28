// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

#include <string.h>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::queue;
using std::string;
using std::vector;

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

struct ListNode;

class Solution {
 public:
  ListNode* rotateRight(ListNode* head, int k) {
    if (!head)
      return head;
    int len = 0;
    auto slow = head;
    auto quick = head;
    auto tmp = head;
    while (tmp->next) {
      tmp = tmp->next;
      len++;
    }
    if (!len)
      return head;

    k %= 1 + len;
    if (!k)
      return head;
    quick = tmp;

    int cnt = len - k;
    while (cnt--) {
      slow = slow->next;
    }

    auto res = slow->next;
    slow->next = nullptr;
    quick->next = head;
    return res;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  return 0;
}