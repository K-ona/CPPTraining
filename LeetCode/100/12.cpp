// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
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

char r1[] = "IXCM"; 
char r5[] = "VLD"; 

class Solution {
 public:
  string intToRoman(int num) {
    string res; 
    int cnt = 0; 
    while (num) {
      int n = num % 10; 
      if (n == 0) {
      } else if (n < 4) {
        while (n--) {
          res = r1[cnt] + res; 
        }
      } else if (n == 4) {
        res = r1[cnt] + (r5[cnt] + res);
      } else if (n == 5) {
        res = r5[cnt] + res; 
      } else if (n < 9) {
        while (n-- > 5) {
          res = r1[cnt] + res; 
        }
        res = r5[cnt] + res; 
      } else if (n == 9) {
        res = r1[cnt] + (r1[cnt + 1] + res); 
      }
      ++cnt; num /= 10;
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