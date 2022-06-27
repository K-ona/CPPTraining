vector<int> get_next(std::string str) {
  vector<int> next(str.size());
  size_t m = str.size();
  int t = next[0] = -1;
  int i = 0;

  while (i < m - 1) {
    if (0 <= t and str[i] != str[t]) {
      t = next[t];
    } else {
      ++i;
      ++t;
      next[i] = t;
    }
  }
  return next;
}

class Solution {
public:
    string shortestPalindrome(string s) {
        string t = s; 
        std::reverse(t.begin(), t.end()); 
        auto str = s + "#" + t;
        __INT32_MAX__
        auto next = get_next(str); 
        int pre = next.back(); 
        return t.substr(0, t.size() - pre - 1) + s;
    }
};
