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
  string multiply(string num1, string num2) {
    if (num1[0] == '0' or num2[0] == '0')
      return "0";
    string res;
    res.reserve(num1.size() + num2.size());
    int n = num1.size();
    int m = num2.size();

    for (int i = n - 1; i >= 0; --i) {
      int ind = 0;
      int rem = 0;
      for (int j = m - 1; j >= 0; --j) {
        ind = n - i + m - j - 2;
        int x = num1[i] - '0';
        int y = num2[j] - '0';
        if (res.size() <= ind)
          res.append("0");
        int z = res[ind] - '0';

        int mulr = x * y + rem + z;
        int cur = mulr % 10;
        rem = mulr / 10;
        res[ind] = cur + '0'; 
      }
      if (rem) {
        if (res.size() <= ind + 1)
          res.append("0");
        res[++ind] = rem + '0';
      }
      cout << res << endl; 
    }
    std::reverse(res.begin(), res.end());
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