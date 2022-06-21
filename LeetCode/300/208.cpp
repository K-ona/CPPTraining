#include <vector>
#include <string>

using std::vector;
using std::string;

class Trie {
    struct node {
        node* next[26]; 
        int cnt; 
        node() {
          for (int i = 0; i < 26; ++i) {
            next[i] = nullptr;
          }
          cnt = 0; 
        }
    };
    node* root; 
public:
    Trie() {
        root = new node; 
    }
    
    void insert(string word) {
        auto cur = root;
        for (auto c: word) {
            if (!cur->next[c - 'a']) cur->next[c - 'a'] = new node; 
            cur = cur->next[c - 'a']; 
        }
        ++cur->cnt; 
    }
    
    bool search(string word) {
        auto cur = root; 
        for (auto c: word) {
            if (!cur->next[c - 'a']) return false; 
            cur = cur->next[c - 'a']; 
        }
        return cur->cnt; 
    }
    
    bool startsWith(string prefix) {
        auto cur = root; 
        for (auto c: prefix) {
            if (!cur->next[c - 'a']) return false; 
            cur = cur->next[c - 'a']; 
        }
        return true; 
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

int main() {
  Trie trie = Trie();
  trie.insert("apple");
  trie.search("apple");   // return True
  trie.search("app");     // return False
  trie.startsWith("app"); // return True
  trie.insert("app");
  trie.search("app");     // return True
}