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

int a[200005]; 
int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */
  int t; 
  for (cin >> t; t--; ) {
    int n;
    ll k; 
    cin >> n >> k; 
    int Max = INT32_MIN, Min = INT32_MAX; 
    for (int i = 0; i < n; i++) {
      cin >> a[i]; 
      Max = std::max(Max, a[i]); 
      Min = std::min(Min, a[i]); 
    }
    int rem = k & 1;  
    int sig = rem ? -1 : 1;
    int add = rem ? Max : -Min; 
    for (int i = 0; i < n; ++i) {
      cout << a[i] * sig + add << ' '; 
    }
    cout << endl; 
  }

  return 0;
}