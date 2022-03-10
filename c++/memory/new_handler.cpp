// 当operator new没能力分配所申请的memory，会抛出一个异常
// std::bad_alloc exception, 某些老旧的编译器则会返回0

// 抛出异常之前，会先（不止一次）调用一个可由client指定的handler

// typedef void(*new_handler)(); 
// new_handler set_new_handler(new_handler p) throw(); 

// 设计良好的new handler只有两个选择：
// 1. 让更多memory可用
// 2. 调用abort() 或 exit() 

#include <new>
#include <iostream>
#include <cassert>

using namespace std;

void noMoreMemory() {
  cerr << "out of memory"; 
  abort(); 
}

int main() {

  set_new_handler(noMoreMemory); 

  int* p = new int[100000000000]; 
  assert(p); 

  return 0; 
}
