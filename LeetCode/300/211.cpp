struct node {
  node* next[26];
  int cnt;
  node() : cnt(0) {
    for (int i = 0; i < 26; ++i)
      next[i] = nullptr;
  }
};
node* global;

class WordDictionary {
  node* root;
 public:
  WordDictionary() { global = root = new node; }

  void addWord(string word) {
    auto cur = root;
    for (auto c : word) {
      if (!cur->next[c - 'a'])
        cur->next[c - 'a'] = new node;
      cur = cur->next[c - 'a'];
    }
    ++cur->cnt;
  }

  bool search(string word, node* rt = global) {
    if (!word.size())
      return rt->cnt;
    for (int i = 0; i < word.size(); ++i) {
      char c = word[i];
      if (c == '.') {
        for (int j = 0; j < 26; ++j) {
          if (rt->next[j] && search(word.substr(i + 1), rt->next[j]))
            return true;
        }
        return false;
      }
      if (!rt->next[c - 'a'])
        return false;
      rt = rt->next[c - 'a'];
    }
    return rt->cnt;
  }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */