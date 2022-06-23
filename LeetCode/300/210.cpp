class Solution {
 public:
  vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<int> G[numCourses];
    vector<int> in(numCourses);

    for (const auto& prerequisity : prerequisites) {
      G[prerequisity[1]].push_back(prerequisity[0]);
      ++in[prerequisity[0]];
    }

    std::queue<int> Q;
    for (int i = 0; i < numCourses; ++i) {
      if (!in[i]) {
        Q.push(i);
      }
    }
    vector<int> res;
    res.reserve(numCourses);
    while (!Q.empty()) {
      res.push_back(Q.front());
      Q.pop();
      for (auto v : G[res.back()]) {
        if (!--in[v])
          Q.push(v);
      }
    }
    if (res.size() != numCourses)
      return {};
    return res;
  }
};