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

int dp[60005]; 
class Solution {
 public:
  int longestValidParentheses(string s) {
    memset(dp, 0, sizeof(dp)); 
    DFS(s, 0); 
    for (int i = 0; i < s.size(); i++) {
        cout << dp[i] << endl; 
    }
    return *std::max_element(dp, dp + s.size()); 
  }

  // 动态规划
  void DFS(const string& s, int i) {
    if (i == s.size()) return ; 
    DFS(s, i + 1); 
    if (s[i] == '(') {
      if (i + 1 < s.size() and s[i + 1] == ')') {
        dp[i] = 2 + dp[i + 2] + dp[i + 2 + dp[i + 2]]; 
        return ;
      } else if(i + 1 < s.size() and s[i + 1] == '(') {
        if (dp[i + 1] and s[1 + i + dp[i + 1]] == ')')
          dp[i] = 2 + dp[i + 1] + dp[i + 2 + dp[i + 1]]; 
      }
    }
  }

  // 栈模拟
  int longestValidParentheses_1(string s) {
    int maxans = 0;
    std::stack<int> stk;
    stk.push(-1);
    for (int i = 0; i < s.length(); i++) {
      if (s[i] == '(') {
        stk.push(i);
      } else {
        stk.pop();
        if (stk.empty()) {
          stk.push(i);
        } else {
          maxans = std::max(maxans, i - stk.top());
        }
      }
    }
    return maxans;
  }
  
  // 常数空间复杂度
  int longestValidParentheses_2(string s) {
    int left = 0, right = 0, maxlength = 0;
    for (int i = 0; i < s.length(); i++) {
      if (s[i] == '(') {
        left++;
      } else {
        right++;
      }
      if (left == right) {
        maxlength = std::max(maxlength, 2 * right);
      } else if (right > left) {
        left = right = 0;
      }
    }
    left = right = 0;
    for (int i = (int)s.length() - 1; i >= 0; i--) {
      if (s[i] == '(') {
        left++;
      } else {
        right++;
      }
      if (left == right) {
        maxlength = std::max(maxlength, 2 * left);
      } else if (left > right) {
        left = right = 0;
      }
    }
    return maxlength;
  }
};


int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  Solution().longestValidParentheses(")(((((()())()()))()(()))("); 
  return 0;
}