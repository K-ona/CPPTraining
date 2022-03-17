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

struct Trie
{
	Trie* son[26];   //son[i]记录的当前节点的子节点 
	int cnt;       //num是当前这个单词出现的次数，视题目而定
  Trie(): cnt(0) {
    for (auto& p: son) { p = nullptr; }
  }
}a[30005];

int cnt = 0;
void build_trie(const std::string& word, Trie* root, Trie arr[]) {
  int l = word.size(); 
  for (int i = 0; i < l; ++i) {
    if (root->son[word[i] - 'a'] == nullptr) {
      root->son[word[i] - 'a'] = &arr[++cnt]; 
    }
    root = root->son[word[i] - 'a']; 
  }
  ++root->cnt; 
}

char st[32]; 
void query_and_add(Trie* root, int& maxh, int h, string& res) {
  if (h > maxh) res = string(st, st + h), maxh = h; 
  for (int i = 0; i < 26; ++i) {
    if (root->son[i] && root->son[i]->cnt) {
      st[h] = 'a' + i; 
      query_and_add(root->son[i], maxh, h + 1, res); 
    }
  }
}

class Solution {
  int max = 0; 
 public:
  string longestWord(vector<string>& words) {
    int n = words.size(); 
    cnt = 0;
    memset(a, 0, sizeof(a)); 
    for (int i = 0; i < n; ++i) {
      build_trie(words[i], a, a); 
    }
    string res; 
    query_and_add(a, max, 0, res); 
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