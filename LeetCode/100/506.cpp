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
    vector<string> findRelativeRanks(vector<int>& score) {
        std::map<int, int> M; 
        for (auto const& x: score) {
            M[x] = 0; 
        }
        int cnt = score.size() + 1; 
        for (auto& x: M) {
            x.second = --cnt; 
        }
        std::vector<string> res; 
        res.reserve(score.size()); 
        for (auto const& x: score) {
            if (M[x] == 1) res.push_back("Gold Medal"); 
            else if (M[x] == 2) res.push_back("Silver Medal"); 
            else if (M[x] == 3) res.push_back("Bronze Medal"); 
            else res.push_back(std::to_string(M[x])); 
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