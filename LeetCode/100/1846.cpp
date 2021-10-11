// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::queue;
using std::string;
using std::vector;

class Solution {
public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
      std::sort(arr.begin(), arr.end());  
      arr[0] = 1; 
      for (int len = arr.size(), i = 1; i < len; ++i) {
        if (arr[i] - arr[i - 1] > 1) {
          arr[i] = arr[i - 1] + 1; 
        }
      }
      return arr.back();
    }
};

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  return 0;
}