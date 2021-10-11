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

class SeatManager {
  std::priority_queue<int, vector<int>, std::greater<int>> PQ; 
public:
    SeatManager(int n) {
      for (int i = 1; i <= n; i++) {
        PQ.push(i); 
      }
    }
    
    int reserve() {
      int res = PQ.top(); 
      PQ.pop(); 
      return res; 
    }
    
    void unreserve(int seatNumber) {
      PQ.push(seatNumber);
    }
};

/**
 * Your SeatManager object will be instantiated and called as such:
 * SeatManager* obj = new SeatManager(n);
 * int param_1 = obj->reserve();
 * obj->unreserve(seatNumber);
 */

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  return 0;
}