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

int main() {
    std::ios_base::sync_with_stdio(false); 
    // #ifdef LOCAL_TEST
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // #endif
    // /* code */

    // double d = 5.12; 
    // void *p = &d; 
    // // static_cast
    // cout << p << endl; 
    // int *q = static_cast<int *>(p); 
    // cout << p << endl; 
    // cout << q << endl; 
    // cout << *q << endl; 

    
    // // const_cast
    // const char *csp = "123456"; 
    // auto str = static_cast<string> (csp); 
    // cout << "str == " << str << endl; 

    // char *sp = const_cast<char *>(csp); 
    // cout << sp << endl; 
    // // sp[1] = '1'; 
    // // cout << sp << endl; 

    int i; double d; const string *ps; char *pc; void *pv; 
    
    pv = (void *)ps; 
    cout << pv << endl; 
    pv = static_cast<void *>(const_cast<string *>(ps));
    cout << pv << endl; 
    
    i = int(*pc); 
    cout << i << endl; 
    i = static_cast<int>(*pc); 
    cout << i << endl; 


    pv = &d; 
    pv = static_cast<void *>(&d); 

    return 0;
}