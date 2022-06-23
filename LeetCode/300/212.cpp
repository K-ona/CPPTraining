#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
int n, m; 

bool vis[20][20]; 

class Solution {
  struct node {
    node* next[26]; 
    int cnt;
    node(): cnt{} {
      for (int i = 0; i < 26; ++i) next[i] = nullptr; 
    }
  };
  
  void insert(string word) {
    node* cur = root; 
    for (auto c: word) {
      if (!cur->next[c - 'a']) cur->next[c - 'a'] = new node; 
      cur = cur->next[c - 'a']; 
    }
    ++cur->cnt; 
  }

  node* root; 
 public:
  vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    n = board.size();
    m = board[0].size();
    root = new node;

    for (auto word: words) {
      insert(word); 
    }

    std::map<string, int> M; 
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        string s; s += board[i][j]; 
        memset(vis, 0, sizeof(vis)); 
        vis[i][j] = true; 
        dfs(i, j, root, M, s, board);
      }
    }

    std::vector<string> res; 
    res.reserve(words.size()); 
    for (auto& [k, v]: M) {
      if (v)
        res.push_back(k);
    }
    return res; 
  }

  void dfs(int x, int y, node* root, std::map<string, int>& M, string& s, vector<vector<char>>& board) {
    if (!root->next[board[x][y] - 'a']) return ;
    root = root->next[board[x][y] - 'a']; 
    if (root->cnt) M[s] = 1; 
    
    for (int i = 0; i < 4; ++i) {
      int tx = x + dx[i]; 
      int ty = y + dy[i];
      if (tx >= 0 && ty >= 0 && tx < n && ty < m && !vis[tx][ty]) {
        s.push_back(board[tx][ty]); 
        vis[tx][ty] = true; 
        dfs(tx, ty, root, M, s, board);
        s.pop_back(); 
        vis[tx][ty] = false; 
      }
    }
  }
};