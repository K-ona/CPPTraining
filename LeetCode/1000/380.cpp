#include <unordered_set>
#include <unordered_map>
#include <random>
#include <vector>

class RandomizedSet {
    std::unordered_map<int, int> m;; 
    std::vector<int> V;
public:
    RandomizedSet() {
        m = {}; 
        V = {}; 
    }
    
    bool insert(int val) {
        if (m.find(val) != m.end()) return false; 
        V.push_back(val); 
        m[val] = V.size() - 1;
        return true; 
    }
    
    bool remove(int val) {
        if (m.find(val) == m.end()) return false; 
        int last = V.back();
        std::swap(V[m[val]], V.back());
        V.pop_back(); 
        m[last] = m[val];
        m.erase(val); 
        return true; 
    }
    
    int getRandom() {
        return *(V.begin() + rand() % V.size()); 
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */