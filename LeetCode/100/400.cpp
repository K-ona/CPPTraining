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
    int findNthDigit(int n) {
        ll cur = 1; 
        int len = 1; 
        while (n - cur * 9 * len > 0) { n -=  cur * 9 * len; cur *= 10; ++len; }
        int cnt = (n - 1) / len; 
        int rem = (len - n % len) % len; 
        int num = cur + cnt;
        while (num && rem) {
          num /= 10; 
          --rem; 
        }
        return num % 10; 
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