// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>

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
    string replaceDigits(string s) {
      for (int i = 0; i < s.size(); ++i) {
        if ('0' <= s[i] and s[i] <= '9') {
          s[i] = s[i - 1] + s[i] - '0'; 
        }
      }
      return s; 
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