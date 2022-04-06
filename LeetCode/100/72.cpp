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
  int res = 500;
 public:
  int minDistance(string word1, string word2) {
    std::map<string, int> M;
    return DFS(word1, word2, M, 0);
  }

  int DFS(string word1, string word2, std::map<string, int>& M, int steps) {
    if (word1 == word2) return 0;

    if (M[word1] != 0) return M[word1];
    if (steps > res) return steps;

    int res = 500;
    // Repalce 
    for (int i = 0; i < word1.size(); ++i) {
      for (char j = 'a'; j <= 'z'; ++j) {
        string tmp = word1;
        tmp[i] = j;
        if (M.count(tmp)) {
          res = std::min(res, DFS(tmp, word2, M, steps + 1));
        }
      }
    }

    // Delete
    for (int i = 0; i < word1.size(); ++i) {
      string tmp = word1; 
      tmp.erase(i, 1); 
      res = std::min(res, DFS(tmp, word2, M, steps + 1));
    }

    // Insert
    for (int i = 0; i <= word1.size(); ++i) {
      for (int j = 'a'; j <= 'z'; ++j) {
        string tmp = word1; 
        tmp.insert(i, 1, j);
        res = std::min(res, DFS(tmp, word2, M, steps + 1));
      }
    }
    return M[word1] = res;
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