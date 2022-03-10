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
}a[1000005];  

int cnt = 0; 
void build_trie(const std::string& word, Trie* root, Trie arr[]) {
  int l = word.size(); 
  for (int i = 0; i < l; ++i) {
    if (root->son[word[l] - 'a']) {
      root = root->son[word[l] - 'a']; 
    } else {
      root->son[word[l] - 'a'] = &arr[++cnt]; 
    }
  }
  ++root->cnt; 
}

int query(const std::string& word, Trie* root, Trie arr[]) {
  int l = word.size(); 
  for (int i = 0; i < l; ++i) {
    if (root->son[word[l] - 'a']) {
      root = root->son[word[l] - 'a']; 
    } else {
      return 0; 
    }
  }
  return root->cnt; 
}


int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  return 0;
}