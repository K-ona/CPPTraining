#include <string>
#include <string_view>

using std::string; 
using std::string_view;
using namespace std::literals::string_view_literals; 

class Solution {
 public:
  int compareVersion(string version1, string version2) {
    string_view s1(version1), s2(version2); 
    int pos1 = 0, pos2 = 0; 
    bool flag = true; 
    while (flag) {
      int v1 = 0; 
      bool flag1 = false;
      if (pos1 < s1.size()) {
        flag1 = true; 
        int tmp = s1.find_first_of('.', pos1);
        // cout << "s1: " << pos1 << " " << tmp << endl; 
        if (tmp == -1) tmp = s1.size(); 
        for (int i = pos1; i < tmp; ++i) {
        //   cout << s1[i] << endl; 
          v1 = v1 * 10 - '0' + s1[i];
        }
        pos1 = tmp + 1; 
      }

      int v2 = 0;
      bool flag2 = false;
      if (pos2 < s2.size()) {
        flag2 = true; 
        int tmp = s2.find_first_of('.', pos2); 
        // cout << "s2: " << pos2 << " " << tmp << endl; 
        
        if (tmp == -1) tmp = s2.size(); 
        for (int i = pos2; i < tmp; ++i) {
        //   cout << s2[i] << endl; 

          v2 = v2 * 10 - '0' + s2[i];
        }
        pos2 = tmp + 1; 
      }
      flag = flag1 + flag2; 
    //   cout << v1 << " " << v2 << endl; 
      if (v1 < v2) return -1; 
      if (v1 > v2) return 1; 
    }
    return 0; 
  }
};