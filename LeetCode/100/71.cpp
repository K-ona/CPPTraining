// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>
#include <stack>

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
  string simplifyPath(string path) {
    std::stack<string> stk;
    int n = path.size();
    stk.push("/");
    for (int i = 0; i < n; ++i) {
      while (i < n and path[i++] == '/')
        ;
      --i;
      string tmp;
      while (i < n and path[i] != '/') {
        tmp += path[i++];
      }
      if (tmp == "..") {
        if (stk.size() > 1)
          stk.pop();
        continue;
      }
      if (tmp.size() == 0 or tmp == ".") {
      } else
        stk.push(tmp);
    }
    string res;
    if (stk.top() == "/")
      return "/";
    while (!stk.empty()) {
      res = stk.top() + "/" + res;
      stk.pop();
    }
    res.pop_back();
    return res.substr(1);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */
  Solution().simplifyPath("/../");

  return 0;
}