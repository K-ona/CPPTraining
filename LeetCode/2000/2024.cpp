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

class Solution {
 public:
  int maxConsecutiveChar(string& answerKey, int k, char ch) {
    int n = answerKey.length();
    int ans = 0;
    for (int left = 0, right = 0, sum = 0; right < n; right++) {
      sum += answerKey[right] != ch;
      while (sum > k) {
        sum -= answerKey[left++] != ch;
      }
      ans = std::max(ans, right - left + 1);
    }
    return ans;
  }

  int maxConsecutiveAnswers(string answerKey, int k) {
    return std::max(maxConsecutiveChar(answerKey, k, 'T'),
               maxConsecutiveChar(answerKey, k, 'F'));
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