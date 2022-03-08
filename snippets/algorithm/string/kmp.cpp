// created by Kona @VSCode
#include <vector>
#include <string>

using std::vector;

vector<int> get_next(std::string str) {
  vector<int> next(str.size());
  size_t m = str.size();
  int t = next[0] = -1;
  int i = 0;

  while (i < m - 1) {
    if (0 <= t and str[i] != str[t]) {
      t = next[t];
    } else {
      ++i;
      ++t;
      next[i] = t;
    }
  }
  return next;
}

int match(std::string T, std::string P) {
  int n = T.size(), i = 0;
  int m = P.size(), j = 0;
  if (!m)
    return 0;
  vector<int> next = get_next(P);
  while (i < n and j < m) {
    if (0 <= j and T[i] != P[j]) {
      j = next[j];
    } else {
      ++i;
      ++j;
    }
  }
  if (j == m)
    return i - j;
  return -1;
}
