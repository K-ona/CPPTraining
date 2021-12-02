// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>

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
    int maxPower(string s) {
        int res = 1; 
        int len = s.size(); 
        for (int i = 1, cnt = 1; i < len; ++i) {
            s[i] == s[i - 1] ? ++cnt : cnt = 1; 
            res = std::max(res, cnt); 
        }
        return res; 
    }
};

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  return 0;
}