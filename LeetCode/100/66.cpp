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
  vector<int> plusOne(vector<int>& digits) {
    int n = digits.size();
    int rem = 1;
    for (int i = n - 1; i >= 0; --i) {
      digits[i] += rem;
      rem = digits[i] / 10;
      digits[i] %= 10;
    }

    if (rem) {
      vector res(n + 1, 0);
      res[0] = 1;
      return res;
    }
    return digits;
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