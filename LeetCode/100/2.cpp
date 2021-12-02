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

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
 public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    int rem = 0;
    ListNode* res = new ListNode;
    ListNode* cur = res;
    while (l1 or l2 or rem) {
      int cnt = rem + (l1 ? l1->val : 0) + (l2 ? l2->val : 0);
      rem = cnt / 10;

      if (l1)
        l1 = l1->next;
      if (l2)
        l2 = l2->next;

      cur->val = cnt % 10;
      if (l1 or l2 or rem)
        cur->next = new ListNode;
      cur = cur->next;
    }
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