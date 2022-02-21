// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>

#include <string.h>

// #define LOCAL_TEST
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
    bool isPalindrome(int x) {
      if (x < 0 || (x % 10 == 0 && x != 0)) return false; 
      int y = 0; 
      while (x > y) {
        y = y * 10 + x % 10;
        x /= 10;
      }
      return x == y || x == y / 10; 
    }
};

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */
  cout << (-96 % 10) << endl;  

  return 0;
}