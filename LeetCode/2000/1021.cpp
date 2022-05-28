class Solution {
 public:
  string removeOuterParentheses(string s) {
    string res;
    std::stack<int> stk;
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] == '(') {
        stk.push(i);
      } else {
        if (stk.size() == 1) {
          res += s.substr(stk.top() + 1, i - stk.top() - 1);
        }
        stk.pop();
      }
    }
    return res;
  }
};