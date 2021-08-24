//created by Kona @VSCode
#include <iostream>
#include <vector>
#include <string>
#include <map>

// #define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::map;
using std::vector;
using std::string;
using std::cout;
using std::endl;

class Solution {
public:
    int getXORSum(vector<int>& arr1, vector<int>& arr2) {
        int n(arr2.size()); 
        for (int i = 1; i < n; ++i) {
            arr2[i] = arr2[i - 1] ^ arr2[i]; 
        }
        int res(arr2[n - 1]); 
        n = arr1.size(); 
        for (int i = 1; i < n; ++i) {
            arr1[i] = arr1[i - 1] ^ arr1[i]; 
        }
        return arr1[n - 1] & res; 
    }
};

int main() {
    std::ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */

    vector<int> a{3}; 
    vector<int> b{6, 7, 8, 9, 10};

    cout << ((b[0] ^ b[1] ^ b[3]) & a[0]) << endl; 
    cout << ((b[0] & a[0]) ^ (a[0] & b[1]) ^ (a[0] & b[3])) << endl; 

    cout << ((b[3] ^ b[1]) & a[0]) << endl; 
    cout << ((b[3] & a[0]) ^ (a[0] & b[1])) << endl; 



    return 0;
}