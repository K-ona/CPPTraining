#include <iostream>
#include <memory>

struct Test {

  Test(Test&& other) {
    std::cout << "in move constructor" << std::endl; 
    p = other.p; 
    other.p = 0; 
  }
  Test(const Test& other) {
    std::cout << "in copy constructor" << std::endl; 
    p = other.p; 
  }
  Test(): p(0) {
    std::cout << "in default constructor" << std::endl; 
  }

 private:
  int p; 
};

Test func() {
  Test t1; 
  std::cout << &t1 << std::endl; 
  return t1; 
}

struct C { /* ... */ };
C f() {
  C c; 
  return c;
}

struct D;
D g(); 

struct D : C {
    D() : C(f()) { }    // no elision when initializing a base-class subobject
    D(int) : D(g()) { } // no elision because the D object being initialized might
                        // be a base-class subobject of some other class
};

// In a return statement, when the operand is the name of a non-volatile object with automatic storage duration, 
// which isn't a function parameter or a catch clause parameter, and which is of the same class type 
// (ignoring cv-qualification) as the function return type. 
// This variant of copy elision is known as NRVO, "named return value optimization".

D g() {
  D d;
  std::cout << &d << std::endl; 
  return d; // : named return value optimization
}



int main() {

  // Test test = Test(Test(func()));
  int i;
  auto p = func(); 
  int x;
  std::cout << &i << std::endl; 
  std::cout << &p << std::endl; 
  std::cout << &x << std::endl; 
}