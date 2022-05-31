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

class ListNode {
 public:
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
 public:
  /**
   * @param head: list's head node
   * @return: reverse print of the list
   * @version: do not affect original list
   */
  vector<int> reversePrint_1(ListNode* head) {
    int array[10005];
    int pos = 10000;
    while (head) {
      array[pos--] = head->val;
      head = head->next;
    }
    return vector<int>(array + pos + 1, array + 10001);
  }

  /**
   * @param head: list's head node
   * @return: reverse print of the list
   * @version: reverse the original list
   */
  vector<int> reversePrint_2(ListNode* head) {
    ListNode* pre = nullptr;
    while (head) {
      auto tmp = head->next;
      head->next = pre;
      pre = head;
      head = tmp;
    }
    vector<int> res;
    while (pre) {
      res.emplace_back(pre->val);
      pre = pre->next;
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