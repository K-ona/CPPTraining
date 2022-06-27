#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <string_view>

using namespace std; 

string s, t; 
unordered_map<string_view, int> M;

bool valid(string s) {
  int cur = 0; 
  for (auto c: s) {
    if (c == '(') ++cur;
    else --cur; 
    if (cur < 0) return false; 
  }
  return cur == 0; 
}

bool dfs(string_view source) {
    if (M.find(source) != M.end()) return M[source]; 
    if (source == t) return true; 
    if (source.size() <= t.size()) return false; 
    int len = source.size(); 
    for (int i = 1; i < len; ++i) {
        if (source[i - 1] == '(' and source[i] == ')') {
            if (dfs(source.substr(0, i - 1) + source.substr(i + 1))) return true; 
        }
    }
    return M[source] = false; 
}


int main() {
    cin >> s >> t; 
    
    if (dfs(s)) {
        cout << "Possible" << endl; 
    } else {
        cout << "Impossible" << endl; 
    }
    return 0; 
}