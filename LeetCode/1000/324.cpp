// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>

#include <string.h>

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
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        int x = (n + 1) / 2;
        int mid = x - 1;
        nth_element(nums.begin(), nums.begin() + mid, nums.end());
        for (int k = 0, i = 0, j = n - 1; k <= j; k++) {
            if (nums[k] > nums[mid]) {
                while (j > k && nums[j] > nums[mid]) {
                    j--;
                }
                swap(nums[k], nums[j--]);
            }
            if (nums[k] < nums[mid]) {
                swap(nums[k], nums[i++]);
            }
        }
        vector<int> arr = nums;
        for (int i = 0, j = x - 1, k = n - 1; i < n; i += 2, j--, k--) {
            nums[i] = arr[j];
            if (i + 1 < n) {
                nums[i + 1] = arr[k];
            }
        }
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