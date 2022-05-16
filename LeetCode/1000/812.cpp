class Solution {
 public:
  int cross(int x1, int y1, int x2, int y2) { return x1 * y2 - x2 * y1; }
  double largestTriangleArea(vector<vector<int>>& points) {
    double res = 0;
    for (int i = 0; i < points.size(); i++) {
      for (int j = i + 1; j < points.size(); j++) {
        for (int k = j + 1; k < points.size(); k++) {
          int x1 = points[j][0] - points[i][0];
          int y1 = points[j][1] - points[i][1];
          int x2 = points[k][0] - points[i][0];
          int y2 = points[k][1] - points[i][1];
          res = max(res, abs(cross(x1, y1, x2, y2) / 2.0));
        }
      }
    }
    return res;
  }
};