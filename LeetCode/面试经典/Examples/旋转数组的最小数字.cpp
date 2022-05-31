#include <vector>

using std::vector;

class Solution {
 public:
  int minArray(vector<int>& numbers) {
    for (int i = numbers.size() - 1; i > 0; --i) {
      if (numbers[i] < numbers[i - 1])
        return numbers[i];
    }
    return numbers[0];
  }
};