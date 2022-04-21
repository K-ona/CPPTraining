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
  string toGoatLatin(string s) {
    string cnta;
    int n = s.size();
    auto isvo = [](char c) {
      return c == 'a' or c == 'e' or c == 'i' or c == 'o' or c == 'u' or
             c == 'A' or c == 'E' or c == 'I' or c == 'O' or c == 'U';
    };
    string ans;
    ans.reserve(n * 2);
    for (int i = 0; i < n; ++i) {
      string tmp;
      while (isalpha(s[i])) {
        tmp += s[i++];
      }
      if (!isvo(tmp[0])) {
        tmp.push_back(tmp[0]);
        tmp = tmp.substr(1);
      }
      ans += tmp + "ma" + (cnta += "a") + " ";
    }
    ans.pop_back();
    return ans;
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