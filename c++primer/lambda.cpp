#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main() {

    int x = 5; 

    auto f = [&]()  {
        x++; // 等价于int tmp = x; tmp++;
    }; 
    f(); 
    cout << x << endl; 


    return 0; 
}
