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

  int get_steps(int res, int n) {
    int steps = 0;
    long long first = res, last = res; 
    while (first <= n) {
      steps += std::min(last, (long long)n) - first + 1;
      first *= 10; 
      last = last * 10 + 9;
    }
    return steps; 
  }

  int findKthNumber(int n, int k) {
    int res = 1; 
    --k; 
    while (k) {
      int steps = get_steps(res, n);  
      if (steps <= k) {
        res++;
        k -= steps;
      } else {
        res *= 10;
        k--;
      }
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