#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int y; 

int main() {

    int x = 5; 

    auto f = [&]()  { 
        y++;
        x++; // 引用
    }; 

    f(); 
    cout << y << endl; 
    cout << x << endl; 

    auto h = [=] () mutable { 
        y++;
        x++; // 复制
    }; 
    h(); 
    cout << y << endl; 
    cout << x << endl; 

    return 0; 
}
