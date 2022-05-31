// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>
#include <stack>

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

class CQueue {
  std::stack<int> ST1, ST2; 
 public:
  CQueue() {}
  void appendTail(int value) {
    ST1.push(value); 
  }
  int deleteHead() {
    if (ST2.empty())
    while (!ST1.empty()) {
      ST2.push(ST1.top()); 
      ST1.pop(); 
    }
    if (ST2.empty()) return -1; 
    int tmp = ST2.top(); 
    ST2.pop(); 
    return tmp; 
  }
};

/**
 * Your CQueue object will be instantiated and called as such:
 * CQueue* obj = new CQueue();
 * obj->appendTail(value);
 * int param_2 = obj->deleteHead();
 */

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  return 0;
}