// created by Kona @VSCode
#include <iostream>
#include <string>

class Foo {
 public:
  int _id; 
  int data; 
  std::string _str; 

  Foo(): _id(0) { std::cout << "defualt ctor.this = " << this << " id = " << _id << std::endl; }
  Foo(int i): _id(i) { std::cout << "normal ctor.this = " << this << " id = " << _id << std::endl; }

  ~Foo() { std::cout << "dtor.this = " << this << " id = " << _id << std::endl; }

  static void* operator new(size_t size); 
  static void operator delete(void* p, size_t size); 
  static void* operator new[](size_t size); 
  static void operator delete[](void* p, size_t size); 

}; 

void* Foo::operator new(size_t size) {
  auto p = malloc(size); 
  std::cout << "Foo::new size = " << size << std::endl; 
  return p; 
}

void* Foo::operator new[](size_t size) {
  auto p = malloc(size); 
  std::cout << "Foo::new[] size = " << size << std::endl; 
  return p; 
}

void Foo::operator delete(void* p, size_t size) {
  std::cout << "Foo::delete size = " << size << std::endl; 
  free(p); 
}

void Foo::operator delete[](void* p, size_t size) {
  std::cout << "Foo::delete[] size = " << size << std::endl; 
  free(p); 
}


int main() {
  
  std::cout << "sizeof(Foo) = " << sizeof(Foo) << std::endl; 
  // 加上::则调用全局operator new 否则调用member operator new
  auto p = new Foo; 
  delete p; 

  p = new Foo(9); 
  delete p; 

  auto q = new Foo[5]; 
  delete[] q; 
  std::cout << *(reinterpret_cast<int *>(q) + 1) << std::endl; 
  return 0;
}