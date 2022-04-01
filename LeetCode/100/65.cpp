// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>
#include <regex>

#include <string.h>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::queue;
using std::string;
using std::vector;

class Solution {
public:
    static const std::regex pattern;

    bool isNumber(string str) {
        return std::regex_match(str, pattern);
    }
};

const std::regex Solution::pattern("[+-]?(?:\\d+\\.?\\d*|\\.\\d+)(?:[Ee][+-]?\\d+)?");


  int main() {
    std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  return 0;
}