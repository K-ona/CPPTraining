#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class Solution {
 public:
  vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
    unordered_map<string, int> M;
    for (int i = list1.size() - 1; i >= 0; --i) {
      M[list1[i]] = i;
    }
    int mins = 2000;
    vector<string> res;
    for (int i = list2.size() - 1; i >= 0; --i) {
      if ((M[list2[i]] != 0 or list1[0] == list2[i]) and
          M[list2[i]] + i <= mins) {
        if (M[list2[i]] + i < mins) {
          mins = M[list2[i]] + i;
          res = vector<string>{list2[i]};
        } else {
          res.emplace_back(list2[i]);
        }
      }
    }
    return res;
  }
};