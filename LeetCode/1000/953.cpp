int alpha[30];
class Solution {
 public:
  bool isAlienSorted(vector<string>& words, string order) {
    for (int i = 0; i < 26; ++i) {
      alpha[order[i] - 'a'] = i;
    }
    auto cmp = [](const string& first, const string& second) -> bool {
      int l = std::min(first.size(), second.size());
      for (int i = 0; i < l; ++i) {
        if (alpha[first[i] - 'a'] > alpha[second[i] - 'a'])
          return false;
        if (alpha[first[i] - 'a'] < alpha[second[i] - 'a'])
          return true;
      }
      if (first.size() <= second.size())
        return true;
      return false;
    };
    int n = words.size();
    for (int i = 1; i < n; ++i) {
      if (!cmp(words[i - 1], words[i]))
        return false;
    }
    return true;
  }
};