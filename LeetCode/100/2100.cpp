// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>
#include <stack>

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

int cnt[100005];
class Solution {
 public:
  vector<int> goodDaysToRobBank(vector<int>& security, int time) {
    int n = security.size();
    memset(cnt, 0, sizeof(cnt));
    if (!time) {
      cnt[0] += 1;
      cnt[n - 1] += 1;
    }
    for (int i = 1, j = 1; i < n; ++i) {
      if (security[i] <= security[i - 1])
        ++j;
      else
        j = 1;
      if (time < j)
        ++cnt[i];
    }
    for (int i = n - 2, j = 1; 0 <= i; --i) {
      if (security[i] <= security[i + 1])
        ++j;
      else
        j = 1;
      if (time < j)
        ++cnt[i];
    }
    vector<int> res;
    for (int i = 0; i < n; ++i) {
      if (cnt[i] == 2) {
        res.emplace_back(i);
      }
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