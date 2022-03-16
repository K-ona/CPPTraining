// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

#include <string.h>

// #define LOCAL_TEST
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
}a[1000005];

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

int query_and_add(const std::string& word, Trie* root, int add_v = 0) {
  int l = word.size(); 
  for (int i = 0; i < l; ++i) {
    if (root->son[word[i] - 'a']) {
      root = root->son[word[i] - 'a']; 
    } else {
      return 0; 
    }
  }
  return root->cnt += add_v; 
}

char st[15]; 
int query_max(Trie* root, int& max, string& res, int h) {
  for (int i = 0; i < 26; ++i) {
    if (root->son[i]) {
      st[h] = 'a' + i; 
      root->son[i]->cnt > max ? (max = root->son[i]->cnt, res = string(st, st + h + 1)) : "";
      query_max(root->son[i], max, res, h + 1); 
    }
  }
  return root->cnt; 
}

int query_min(Trie* root, int& min, string& res, int h) {
  for (int i = 0; i < 26; ++i) {
    if (root->son[i]) {
      st[h] = 'a' + i;
      if (root->son[i]->cnt > 0 and root->son[i]->cnt < min) {
        min = root->son[i]->cnt, res = string(st, st + h + 1);
      }
      query_min(root->son[i], min, res, h + 1); 
    }
  }
  return root->cnt; 
}

class AllOne {
 public:
  AllOne() { cnt = 0; memset(a, 0, sizeof(a)); }

  void inc(string key) { 
    build_trie(key, a, a);
  }

  void dec(string key) {
    query_and_add(key, a, -1); 
  }

  string getMaxKey() {
    string res = ""; 
    int max = 0; 
    query_max(a, max, res, 0); 
    return res; 
  }

  string getMinKey() {
    string res = ""; 
    int min = 100000; 
    query_min(a, min, res, 0); 
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

  AllOne all = AllOne(); 

  all.inc("hello"); 
  all.inc("hello"); 
  cout << all.getMaxKey() << endl; 
  cout << all.getMinKey() << endl; 
  all.inc("hello");
  all.inc("leet"); 
  cout << all.getMaxKey() << endl; 
  cout << all.getMinKey() << endl; 

  // all.inc("a");
  // all.inc("b");
  // all.inc("b");
  // all.inc("c");
  // all.inc("c");
  // all.inc("c");
  // all.dec("b");
  // all.dec("b");
  // cout << all.getMinKey() << endl; 
  // all.dec("a");
  // cout << all.getMaxKey() << endl; 
  // cout << all.getMinKey() << endl; 

  return 0;
}