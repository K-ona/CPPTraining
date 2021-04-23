#include <vector>
#include <iostream>

using std::vector; 
using std::endl; 
using std::cout; 

class A {
    int val; 
public: 
    A& operator=(const A& a) {
        cout << "==" << endl; 
        this->val = a.val; 
        return *this; 
    }
    A(const int x) {
        val = x; 
        cout << "construct1111" << endl; 
    }
    explicit A(const A &x) {
        this->val = x.val; 
        cout << "construct2222" << endl; 
    }
}; 

int main() {

    vector<int> V{1, 2, 3, 4, 5}; 
    auto p = V.end(); 
    cout << *(p - 5) << endl; 
    cout << *(--p) << endl; 
    cout << "sep dis == " << V.end() - p << endl; 
    // vector<const int> V1{1, 2, 3, 4, 5}; error

    // int cnt = 123; 
    // int a[cnt]; error
    
    int a[123] = {0}; 
    cout << a[2] << endl; 
    
    cout << *std::begin(a) << endl; 
    cout << *(std::end(a) - 1) << endl; 

    A *p1 = new A(1); 
    A *p2 = new A(1); 

    auto p3 = p1 + 1; 
    cout << p3 - p1 << endl; 
    delete p2; 
    delete p1; 

    int *ptr1 = nullptr; 
    int *ptr2 = nullptr; 
    cout << ptr1 - ptr2 << endl;

    int aa[] = {1, 2, 3, 4, 5}; 
    int *p_1 = aa + 5; 
    int *p_2 = aa + 0; 

    cout << p_2 - p_1 << endl; 
    p_1 += p_2 - p_1; 

    cout << *p_1 << endl; 

    return 0; 
}