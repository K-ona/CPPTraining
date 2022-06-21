class Solution {
 public:
  string defangIPaddr(string address) {
    string res;
    int i = 0;
    do {
      while (isdigit(address[i])) {
        res += address[i++];
      }
      ++i;
    } while (i < address.size() && (res += "[.]", 1));
    return res;
  }
};