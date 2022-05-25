int len[30];
class Solution {
 public:
  int findSubstringInWraproundString(string p) {
    int l = 0, r = 0;
    int n = p.size();
    long long ans = 0;
    memset(len, 0, sizeof(len));
    while (r < n) {
      while (r + 1 < n && p[r + 1] == ('a' + (p[r] - 'a' + 1) % 26))
        ++r;
      for (int i = 0, cnt = r - l + 1, sz = std::min(26, cnt); i < sz; ++i) {
        if (int inc = cnt - i, ind = i + l; len[p[ind] - 'a'] < inc) {
          ans += inc - len[p[ind] - 'a'];
          len[p[ind] - 'a'] = inc;
        }
      }
      l = ++r;
    }
    return ans;
  }
};