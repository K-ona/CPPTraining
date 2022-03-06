#include <iostream>

class allocator {
 private:
  // 内置next指针定义，通过强制类型转换节约指针空间，与使用Union类似
  struct obj {
    struct obj* next; // embedded pointer
  };
 
 public:
  void* allocate(size_t); 
  void deallocate(void*, size_t); 

 private:
  obj* freeStore = nullptr; 
  int const CHUNK = 20;
}; 

void* allocator::allocate(size_t size) {
  obj* p; 
  if (!freeStore) {
    freeStore =  p = static_cast<obj*>(malloc(size * CHUNK)); 

    for (int i = 0; i < CHUNK - 1; ++i) {
      p->next = reinterpret_cast<obj*>(reinterpret_cast<char*>(p) + size);
      p = p->next; 
    }
    p->next = nullptr; 
  }
  p = freeStore; 
  freeStore = freeStore->next; 
  return p; 
}

void allocator::deallocate(void* ptr, size_t size) {
  static_cast<obj*>(ptr)->next = freeStore; 
  freeStore = static_cast<obj*>(ptr); 
}

// 客户类的使用方法
class Foo { 
 public:
  long L; 
  std::string str; 

  /*                */
  static allocator alloc;
  /*                */

 public:
  Foo(long l): L(l) {}

  /*                */
  static void* operator new(size_t size) {
    return alloc.allocate(size); 
  }
  static void operator delete(void* ptr, size_t size) {
    alloc.deallocate(ptr, size); 
  }
  /*                */
}; 

allocator Foo::alloc; 

// TEST
int main() {
  
  Foo* p[100]; 
  std::cout << "sizeof(Foo) = " << sizeof(Foo) << std::endl; 
  std::cout << "alignment of (std::string) = " << std::alignment_of_v<std::string> << std::endl; 
  std::cout << "sizeof(std::string) = " << sizeof(std::string) << std::endl; 
  std::cout << "sizeof(allocator) = " << sizeof(allocator) << std::endl; 

  for (int i = 0; i < 23; ++i) {
    p[i] = new Foo(i); 
  }

  for (int i = 0; i < 23; ++i) {
    std::cout << p[i] << " " << p[i]->L << std::endl; 
  }

  return 0; 
}