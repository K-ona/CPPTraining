#include <string>
#include <string_view>

using std::string;
using std::string_view;

class Solution {
 public:
  string reverseWords(string s) {
    string res;
    std::string_view sv(s);
    sv.remove_prefix(std::min(sv.find_first_not_of(" "), sv.size()));

    for (int n = sv.size(); n >= 0;) {
      if (auto pos = sv.find_last_not_of(" "); pos != string_view::npos)
        sv.remove_suffix(sv.size() - pos - 1);
      int oc = sv.find_last_of(" ");
      if (!res.empty())
        res += " ";
      res += sv.substr(oc + 1);
      sv.remove_suffix(sv.size() - oc - 1);
      n = oc - 1;
    }
    return res;
  }
};

class Solution {
 public:
  string reverseWords(string s) {
    // 反转整个字符串
    reverse(s.begin(), s.end());

    int n = s.size();
    int idx = 0;
    for (int start = 0; start < n; ++start) {
      if (s[start] != ' ') {
        // 填一个空白字符然后将idx移动到下一个单词的开头位置
        if (idx != 0)
          s[idx++] = ' ';

        // 循环遍历至单词的末尾
        int end = start;
        while (end < n && s[end] != ' ')
          s[idx++] = s[end++];

        // 反转整个单词
        reverse(s.begin() + idx - (end - start), s.begin() + idx);

        // 更新start，去找下一个单词
        start = end;
      }
    }
    s.erase(s.begin() + idx, s.end());
    return s;
  }
};

// 作者：LeetCode-Solution
// 链接：https://leetcode.cn/problems/reverse-words-in-a-string/solution/fan-zhuan-zi-fu-chuan-li-de-dan-ci-by-leetcode-sol/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。