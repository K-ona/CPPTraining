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

class Trie {
 public:
  bool isWord;
  // pos记录单词在words中的位置
  int pos;
  Trie* nodes[26];
  Trie() {
    isWord = false;
    for (int i = 0; i < 26; i++) {
      nodes[i] = nullptr;
    }
    pos = -1;
  }
};
class Solution {
 public:
  Trie* root;
  map<string, int> m;
  vector<string> ws;
  vector<int> findSubstring(string s, vector<string>& words) {
    root = new Trie();
    int pos = 0;
    ws = words;
    for (string str : words) {
      insert(str, pos++);
      m[str] += 1;
    }

    int n = s.length();
    int len = words[0].length();
    int num = words.size();
    vector<int> ans;
    for (int i = 0; i <= n - len * num; i++) {
      if (query(s, i, len, num))
        ans.push_back(i);
    }
    return ans;
  }
  bool query(string s, int start, int len, int num) {
    // vector<bool>flag(num);
    map<string, int> m1(m);

    // num个字符串
    while (num > 0) {
      int l = 0;
      Trie* cur = root;
      // len个字符是一个字符串
      while (l < len) {
        //不存在这个字符，false
        if (cur->nodes[s[start] - 'a'] == nullptr)
          return false;
        cur = cur->nodes[s[start] - 'a'];
        l++;
        start++;
      }
      //如果-1后，value值<0，则说明不满足题意
      if (--m1[ws[cur->pos]] < 0)
        return false;
      num--;
    }
    return true;
  }

  void insert(string str, int pos) {
    Trie* cur = root;
    for (char ch : str) {
      if (cur->nodes[ch - 'a'] == nullptr) {
        cur->nodes[ch - 'a'] = new Trie();
      }
      cur = cur->nodes[ch - 'a'];
    }
    cur->isWord = true;
    cur->pos = pos;
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