class Solution {
 public:
  vector<int> shortestToChar(string s, char c) {
    int n = s.size();
    vector<int> ans(n);
    int first = -1;
    for (int i = 0; i < n; ++i) {
      if (s[i] == c) {
        for (int j = first + 1; j < i; ++j) {
          ans[j] = std::min(first == -1 ? INT_MAX : (j - first), i - j);
        }
        first = i;
      }
    }
    if (s[n - 1] != c) {
      for (int j = first + 1; j < n; ++j) {
        ans[j] = j - first;
      }
    }
    return ans;
  }
};