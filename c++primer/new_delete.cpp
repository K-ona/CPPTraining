//created by Kona @VSCode
#include<bits/stdc++.h>

using namespace std;

int& fun() {
    int x = 1; 
    return x; 
}
int main() {
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */

    // new int(*[10])(); // error: parsed as (new int) (*[10]) ()
    auto p = new (int (*[10])()); // okay: allocates an array of 10 pointers to functions
    cout << sizeof p << endl; 
    cout << sizeof p[0] << endl; 

    return 0;
}