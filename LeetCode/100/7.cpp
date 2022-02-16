// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
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
  int reverse(int x) {
    int low = 1 << 31; 
    int high = ~low; 
    int y = 0; 
    while (x) {
      if (y > high / 10 or y < low / 10) return 0;
      y = y * 10 + x % 10; 
      x /= 10; 
    }
    return y; 
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */
    int low = 1 << 31; 
    int high = ~low;
    cout << low << " " << high << endl; 
  return 0;
}