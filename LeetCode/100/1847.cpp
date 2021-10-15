// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::queue;
using std::set;
using std::string;
using std::vector;

class Solution {
 public:
  vector<int> closestRoom(vector<vector<int>>& rooms,
                          vector<vector<int>>& queries) {
    std::sort(rooms.begin(), rooms.end(),
              [&](vector<int> &first, vector<int> &second) -> bool {
                return first[1] > second[1];
              });
    for (int i = 0; i < queries.size(); ++i) {
      queries[i].push_back(i);
    }
    std::sort(queries.begin(), queries.end(),
              [&](vector<int> &first, vector<int> &second) -> bool {
                  return first[1] > second[1];
              });

    vector<int> res(queries.size(), 0);

    set<int> Sup;
    for (int i = 0, l = 0; i < queries.size(); ++i) {
    //   cout << queries[i][1] << endl; 
      while (l < rooms.size() && rooms[l][1] >= queries[i][1])
        Sup.insert(rooms[l++][0]);

      auto pos = Sup.lower_bound(queries[i][0]);
      if (Sup.empty())
        res[queries[i][2]] = -1;
      else if (pos == Sup.begin())
        res[queries[i][2]] = *pos;
      else if (abs(*pos - queries[i][0]) >= abs(*(--pos) - queries[i][0])) {
        res[queries[i][2]] = *pos;
      } else {
        res[queries[i][2]] = *(++pos);
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