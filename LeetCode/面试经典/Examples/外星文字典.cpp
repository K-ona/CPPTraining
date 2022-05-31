#include <string>
#include <vector>
#include <string.h>

using std::string;
using std::vector;


int deg[30];
bool vis[30]; 
vector<int> to[30];

class Solution {
 public:
  string alienOrder(vector<string>& words) {
    int n = words.size();
    for (int i = 0; i < 26; ++i) to[i].resize(0);
    memset(deg, 0, sizeof(deg)); 
    memset(vis, 0, sizeof(vis)); 

    for (auto c: words[0]) vis[c - 'a'] = true;
    for (int i = 1; i < n; ++i) {
      int min = std::min(words[i - 1].size(), words[i].size());
      for (auto c: words[i]) vis[c - 'a'] = true;
      bool flag = false; 
      for (int j = 0; j < min; ++j) {
        if (words[i - 1][j] != words[i][j]) {
          to[words[i - 1][j] - 'a'].push_back(words[i][j] - 'a');
          ++deg[words[i][j] - 'a'];
          flag = true; 
          break;
        }
      }
      if (!flag and words[i].size() < words[i - 1].size()) return ""; 
    }

    string res;
    bool flag = true;
    while (flag) {
      flag = false;
      for (int i = 0; i < 26; ++i) {
        if (!deg[i] && vis[i]) {
        //   cout << char(i + 'a') << endl; 
          deg[i] = -1; 
          flag = true;
          res += 'a' + i;
          for (auto x : to[i]) {
            --deg[x];
          }
        }
      }
    }
    int cnt = 0; 
    for (int i = 0; i < 26; ++i) {
        cnt += vis[i];
    }
    return res.size() == cnt ? res : ""; 
  }
};