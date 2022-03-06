#include <iostream>
#include <string>

using std::cin;
using std::string;
using std::endl;  
using std::cout;

class test_class{
    string name; 
public: 
    test_class(): name("NO Name") { cout << "in default" << endl; }
    test_class(string n): name(n) { cout << "in n" << endl; }
    test_class(const test_class & other): name(other.name) { cout << "in x" << endl; }

    test_class& operator=(test_class A) { 
        cout << "in =" << endl; 
        this->name = A.name; return *this; 
    }

}; 

struct vector3 {
    double x, y, z; 
    int id; 
};

class entity {
private:
    
public:
    void print() const {}
};

class Scop {
private:
    entity *eptr; 
public:
    Scop(entity *pt): eptr(pt){}
    ~Scop(){
        delete eptr; 
    }

    const entity *operator->() const{
        return eptr; 
    }
};

int main()
{

    test_class A; 
    test_class B("Kona"); 
    test_class C = test_class("Kona"); 
    test_class D = C; 

    // cout << sizeof(test_class) << endl; 
    using namespace std::literals; 
    test_class E = "Kona"s; //隐式构造

    // 获取偏移量
    int offs = (int)&((vector3 *)nullptr)->id; 
    cout << offs << endl; 
    cout << sizeof(vector3) << endl; 
 
    Scop scop1 = new entity(); 
    const Scop scop2 = new entity(); 
    scop2->print();  
    
    return 0;
}