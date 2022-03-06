// 内存管理关键问题：
// 1，分配速度
// 2. 空间利用率

#include <cstddef> 
#include <iostream>

using namespace std; 

class Screen {
 public:
  Screen(int x): i(x) {}
  int get() { return i; }

  static void* operator new(size_t); 
  static void operator delete(void*, size_t); 

 private:
  Screen* next; 
  static Screen* freeStore; 
  static const int screenChunk; 

 private:
  int i; 
}; 

Screen* Screen::freeStore = nullptr; 
const int Screen::screenChunk = 24; 

void* Screen::operator new(size_t size) {
  Screen* p; 
  // 线程不安全
  // 当内存块的链表为空时（或到达尾端时）申请一大块内存
  if(!freeStore) {
    size_t chunk = screenChunk * size; 
    freeStore = p = reinterpret_cast<Screen*>(new char[chunk]); 
    
    for (; p != &freeStore[screenChunk - 1]; ++p) {
      p->next = p + 1; 
    }
    p->next = nullptr; 
  }
  p = freeStore; 
  freeStore = freeStore->next; 
  return p; 
}

void Screen::operator delete(void* ptr, size_t size) {
  // cout << "delete size = " << size << endl; 
  (static_cast<Screen*>(ptr))->next = freeStore; 
  freeStore = static_cast<Screen*>(ptr); 
}

// TEST
int main() {

  cout << sizeof(Screen) << endl; 

  size_t constexpr N = 100; 
  Screen* p[N]; 
  for (int i = 0; i < N; ++i) {
    p[i] = new Screen(i); 
  }

  // 地址连在一起，说明没有额外的cookies
  // 没连在一起也说明不了问题，分配大块内存不一定会连在一起
  for (int i = 0; i < 10; ++i) {
    cout << p[i] << endl; 
  }

  for (auto &x: p) {
    delete x; 
  }

  return 0; 
}