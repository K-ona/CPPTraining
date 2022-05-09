char op[] = {'A', 'C', 'G', 'T'}; 
class Solution {
 public:
  int minMutation(string start, string end, vector<string>& bank) {
    std::unordered_map<string, int> M; 
    for (auto &s: bank) {
      M[s] = 1; 
    }
    if (!M[end]) return -1; 
    M[start] = 1; 
    std::queue<std::pair<string, int>> Q;
    Q.push({start, 0}); 

    while (!Q.empty()) {
      start = Q.front().first; 
      int steps = Q.front().second; 
      Q.pop();
      if (start == end) return steps; 

      for (int i = 0; i < 8; ++i) {
        char c = start[i];
        for (int j = 0; j < 4; ++j) {
          if (op[j] != start[i]) {
            start[i] = op[j]; 
            if (M[start] == 1) {
              ++M[start];
              Q.push({start, steps + 1});
            }
            start[i] = c; 
          }
        }
      }
    }
    return -1; 
  }
};