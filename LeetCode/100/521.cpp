// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
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
  int findLUSlength(string a, string b) {
    if (a.size() > b.size())
      std::swap(a, b);
    if (a.size() != b.size())
      return b.size();
    int end = b.size() - 1;
    for (int i = a.size() - 1; i >= 0; --i) {
      bool flag = false;
      for (int j = end; j >= 0; --j) {
        if (b[j] == a[i]) {
          end = j - 1;
          flag = true;
          break;
        }
      }
      if (!flag) {
        cout << "i == " << i << endl;
        return a.size();
      }
    }
    return -1;
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