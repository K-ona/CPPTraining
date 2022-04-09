#include <stack>
#include <string>

class Solution {
 public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param str string字符串
   * @return string字符串
   */

  std::string compress(std::string str) {
    // write code here
    std::stack<std::string> st;
    std::stack<int> st2; // 记录字符串重复数量
    int len = str.size();
    int pre = 0; 
    for (int i = 0; i < len; ++i) {
      if (str[i] == '[') {
        int cnt = 0; 
        while (std::isdigit(str[++i])) {
          cnt = cnt * 10 + str[i] - '0';
        }
      }
    }

  }
};