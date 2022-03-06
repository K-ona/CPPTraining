// created by Kona @VSCode
#include <iostream>
#include <string>

class Foo {
 public:
  int _id; 
  int data; 
  std::string _str; 

  Foo(): _id(0) { std::cout << "defualt ctor.this = " << this << " id = " << _id << std::endl; }
  Foo(int i): _id(i) { std::cout << "normal ctor.this = " << this << " id = " << _id << std::endl; throw std::runtime_error(""); }

  ~Foo() { std::cout << "dtor.this = " << this << " id = " << _id << std::endl; }

  static void* operator new(size_t size); 
  static void* operator new(size_t size, void* start); 
  static void* operator new(size_t size, long extra); 
  static void* operator new(size_t size, long extra, char init); 
  static void operator delete(void* p, size_t size); 
  static void operator delete(void* p, size_t size, void* ); 
  static void operator delete(void* p, size_t size, long ); 
  static void operator delete(void* p, size_t size, long, char); 
}; 

void* Foo::operator new(size_t size) {
  auto p = malloc(size); 
  std::cout << "Foo::new(size_t) size = " << size << std::endl; 
  return p; 
}

void* Foo::operator new(size_t size, void* start) {
  std::cout << "Foo::new(size_t, void*) size = " << size << std::endl; 
  return start; 
}

void* Foo::operator new(size_t size, long extra) {
  auto p = malloc(size + extra); 
  std::cout << "Foo::new(size_t, long) size = " << size + extra << std::endl; 
  return p; 
}

void* Foo::operator new(size_t size, long extra, char init) {
  auto p = malloc(size + extra); 
  std::cout << "Foo::new(size_t, long, char) size = " << size + extra << std::endl; 
  return p; 
}

void Foo::operator delete(void* p, size_t size) {
  std::cout << "Foo::delete(void*, size_t) size = " << size << std::endl; 
  free(p); 
}

void Foo::operator delete(void* p, size_t size, void* start) {
  std::cout << "Foo::delete(void*, size_t, void*)  size = " << size << std::endl; 
}

void Foo::operator delete(void* p, size_t size, long extra) {
  std::cout << "Foo::delete(void*, size_t, long)  size = " << size << std::endl; 
}

void Foo::operator delete(void* p, size_t size, long extra, char c) {
  std::cout << "Foo::delete(void*, size_t, long, char)  size = " << size << std::endl; 
}

int main() {
  
  // 加上::则调用全局operator new 否则调用member operator new
  Foo start; 
  Foo* p1 = new Foo; 
  Foo* p2 = new(&start) Foo; 
  Foo* p3 = new(5) Foo; 
  Foo* p4 = new(5, 'c') Foo; 
  
  // 先分配内存再抛出异常
  // Foo* p5 = new(5) Foo(1); 
  // Foo* p6 = new(5, 'c') Foo(1); 
  // Foo* p7 = new(&start) Foo(1); 
  // Foo* p8 = new Foo(1); 



  return 0;
}