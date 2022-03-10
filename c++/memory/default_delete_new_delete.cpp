#include <iostream>

class Foo { 
 public:
  long L; 
  std::string str; 
  Foo(long l): L(l) {}

  // error
  // static void* operator new(size_t size) = default; 
  static void* operator new(size_t size) = delete; 

}; 

class Goo { 
 public:
  long L; 
  std::string str; 
  Goo(long l): L(l) {}
}; 

int main() {
  
  // error
  // new Foo(1); 

  return 0; 
}