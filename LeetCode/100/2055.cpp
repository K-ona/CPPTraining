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

int sum[100005];
class Solution {
 public:
  vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
    memset(sum, 0, sizeof(sum));
    int len = s.size();
    bool flag = false;
    if (s[0] == '|')
      flag = true;

    vector<int> candles;
    candles.reserve(len);

    for (int i = 0; i < len; ++i) {
      if (s[i] == '|')
        candles.push_back(i);
    }

    for (int i = 1, j = 0; i < len; ++i) {
      sum[i] = sum[i - 1];
      if (s[i] == '|') {
        sum[i] += j;
        j = 0;
        flag = true;
      } else if (flag)
        ++j;
    }

    vector<int> res(queries.size());
    for (int i = 0; i < queries.size(); ++i) {
      auto query = queries[i];
      auto l = std::lower_bound(candles.begin(), candles.end(), query[0]);
      auto r = std::lower_bound(candles.begin(), candles.end(), query[1]);
      if (l == r)
        continue;
      if (candles.back() < query[1])
        --r;
      else if (*r > query[1])
        --r;
      res[i] = sum[*r] - sum[*l];
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