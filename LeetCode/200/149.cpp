class Solution {
 public:
  int maxPoints(vector<vector<int>>& points) {
    if (points.size() == 1)
      return 1;

    unordered_map<double, int> hash;
    int res = 0;
    int n = points.size();
    for (int i = 0; i < n; i++) {
      int same_x = 1;
      for (int j = i + 1; j < n; j++) {
        // 垂直于x轴的直线
        if (points[i][0] == points[j][0]) {
          same_x++;
        }
        // 记录经过point[i]的斜率为k的点的个数
        else {
          double dx = points[i][0] - points[j][0];
          double dy = points[i][1] - points[j][1];
          double k = dy / dx;
          if (!hash.count(k))
            hash[k] = 2;
          else
            hash[k]++;
        }
      }
      for (auto x : hash)
        res = max(res, x.second);
      res = max(res, same_x);
      hash.clear();
    }
    return res;
  }
};