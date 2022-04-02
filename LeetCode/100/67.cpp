// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>

#include <string.h>

// #define LOCAL_TEST
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
  string addBinary(string a, string b) {
    int i = a.size(), j = b.size();
    int end = std::max(j, i) + 1;
    string res(end, '0');
    int rem = 0;
    while (i and j) {
      int tmp = a[--i] - '0' + b[--j] - '0' + rem;
      res[--end] = tmp % 2 + '0';
      rem = tmp / 2;
    }
    while (i) {
      int tmp = a[--i] - '0' + rem;
      res[--end] = tmp % 2 + '0';
      rem = tmp / 2;
    }
    while (j) {
      int tmp = b[--j] - '0' + rem;
      res[--end] = tmp % 2 + '0';
      rem = tmp / 2;
    }
    if (rem)
      res[--end] = rem + '0';
    return res.substr(end); 
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  cout << Solution().addBinary("1", "111") << endl;

  return 0;
}