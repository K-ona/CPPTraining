class Solution {
 public:
  string convertToTitle(int columnNumber) {
    string res;
    while (columnNumber) {
      res = char((columnNumber - 1) % 26 + 'A') + res;
      columnNumber = (columnNumber - 1) / 26;
    }
    return res;
  }
};