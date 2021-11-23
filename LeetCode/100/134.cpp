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
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
      int len = static_cast<int>(gas.size());
      for (int i = 0; i < len; ++i) {
        gas[i] -= cost[i]; 
      }
      
      int sum = 0; 
      int Min = 0;
      int mini = -1;  
      for (int i = 0; i < len; ++i) {
        sum += gas[i]; 
        Min = std::min(Min, sum); 
        mini = Min == sum ? i : mini;
      }
      if (sum >= 0)
        return (mini + 1) % len; 
      return -1; 
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