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
    int myAtoi(string &s) {
      long long res = 0; 
      long long high = (1ll << 31);
      int sign = 1;
      int ind = 0; 
      int len = s.size(); 
      if (len == 0) return 0; 
      while (ind < len and s[ind++] == ' ') continue; 
      --ind; 
      if (s[ind] == '-' or s[ind] == '+') {
        sign = s[ind] == '-' ? -1 : 1; 
        ++ind; 
      }

      while (ind < len and std::isdigit(s[ind])) {
        res = res * 10 + s[ind++] - '0'; 
        if (res > high) {
        //   cout << "res == " << res << endl; 
          res = high;
          break;
        }
      }
      return sign == -1 ? sign * res : (res == high ? --res : res); 
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

