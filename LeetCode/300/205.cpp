class Solution {
 public:
  bool isIsomorphic(string s, string t) {
    vector<vector<int>> map(2, vector<int>(300, -1));
    if (s.size() != t.size())
      return false;
    int n = s.size();
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
      if (map[0][s[i]] == -1 && map[1][t[i]] == -1) {
        map[0][s[i]] = map[1][t[i]] = cnt++;
      } else if (map[1][t[i]] != -1 && map[0][s[i]] != -1 &&
                 map[0][s[i]] == map[1][t[i]]) {
      } else {
        return false;
      }
    }
    return true;
  }
};