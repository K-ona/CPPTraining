class Solution {
 public:
  int computeArea(int ax1,
                  int ay1,
                  int ax2,
                  int ay2,
                  int bx1,
                  int by1,
                  int bx2,
                  int by2) {
    int len1 = in_len(ax1, ax2, bx1, bx2);
    int len2 = in_len(ay1, ay2, by1, by2);
    // cout << len1 << " " << len2 << endl;
    int sum = (ax2 - ax1) * (ay2 - ay1) + (bx2 - bx1) * (by2 - by1);
    return sum - len1 * len2;
  }

  int in_len(int x1, int x2, int y1, int y2) {
    if (x1 > y1) {
      std::swap(x1, y1);
      std::swap(x2, y2);
    }
    return std::max(std::min(x2, y2) - y1, 0);
  }
};