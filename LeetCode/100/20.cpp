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

class Solution {
 public:
  bool isValid(string s) {
    std::stack<char> S; 
    for (auto c : s) {
      if (c == '(' or c == '[' or c == '{') {
        S.push(c); 
        continue;
      }
      if (c == ')') {
        if (S.empty() or S.top() != '(') return false; 
        S.pop(); 
      }
      if (c == ']') {
        if (S.empty() or S.top() != '[') return false; 
        S.pop(); 
      }   
      if (c == '}') {
        if (S.empty() or S.top() != '{') return false; 
        S.pop(); 
      }
    }
    if (S.empty()) return true; 
    return false; 
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  Solution().isValid("()[]{}"); 

  return 0;
}