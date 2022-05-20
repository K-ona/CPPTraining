#include <list>
#include <unordered_map>

using namespace std;

class LRUCache {
  list<pair<int, int>> data;
  unordered_map<int, list<pair<int, int>>::iterator> M;
  int sz;

 public:
  LRUCache(int capacity) : sz(capacity) {}

  int get(int key) { 
      if (M.find(key) == M.end())
        return -1; 
      auto res = *M[key];
      data.erase(M[key]);
      data.push_front(res);
      M[key] = data.begin();

      return res.second; 
    }

  void put(int key, int value) {
    if (M.find(key) != M.end()) {
      data.erase(M[key]);
    } else if (M.size() == sz) {
      M.erase(M.find(data.back().first));
      data.pop_back();
    }
    data.push_front({key, value});
    M[key] = data.begin();
  }
};
/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */