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

class Solution {
 public:
  int getSteps(int curr, long n) {
    int steps = 0;
    long first = curr;
    long last = curr;
    while (first <= n) {
      steps += std::min(last, n) - first + 1;
      first = first * 10;
      last = last * 10 + 9;
    }
    return steps;
  }

  int findKthNumber(int n, int k) {
    int curr = 1;
    k--;
    while (k > 0) {
      int steps = getSteps(curr, n);
      if (steps <= k) {
        k -= steps;
        curr++;
      } else {
        curr = curr * 10;
        k--;
      }
    }
    return curr;
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