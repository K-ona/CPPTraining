class Solution {
 public:
  int findClosest(vector<string>& words, string word1, string word2) {
    int p1 = -1, p2 = -1;
    int ans = 100000;
    for (int i = 0; i < words.size(); ++i) {
      if (words[i] == word1) {
        p1 = i;
        if (~p2)
          ans = std::min(ans, p1 - p2);
      } else if (words[i] == word2) {
        p2 = i;
        if (~p1)
          ans = std::min(ans, p2 - p1);
      }
    }
    return ans;
  }
};