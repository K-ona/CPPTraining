#include <algorithm>
#include <string>
#include <vector>

using std::pair;
using std::string;
using std::vector;

class Solution {
 public:
  vector<string> reorderLogFiles(vector<string>& logs) {
    vector<string> res, dig;
    vector<pair<string, string>> tmp;
    tmp.reserve(100);
    dig.reserve(100);
    res.reserve(100);

    for (const auto& s : logs) {
      string id;
      int i;
      for (i = 0; s[i] != ' '; ++i)
        ;
      id = s.substr(0, i);

      if (isdigit(s[i + 1]))
        dig.push_back(std::move(s));
      else
        tmp.emplace_back(pair(s.substr(i + 1), id));
    }

    std::sort(tmp.begin(), tmp.end());
    for (const auto& x : tmp) {
      res.push_back(x.second + " " + x.first);
    }
    for (auto& x : dig) {
      res.push_back(std::move(x));
    }
    return res;
  }
};