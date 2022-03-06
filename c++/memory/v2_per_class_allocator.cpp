// 内存管理关键问题：
// 1，分配速度
// 2. 空间利用率

// 与第一版的区别在于使用了Union（内存管理中常用的技巧）
// 在构造前（被分配前）将前四个字节视为next指针，节省了一个指针的大小

#include <iostream>

class Airplane {
 private:
  struct AirplaneRep {
    unsigned long miles;
    char type;
  };

 private:
  union {
    /* data */
    AirplaneRep rep;
    Airplane* next;
  };

 public:
  unsigned long getMiles() { return rep.miles; }
  char getType() { return rep.type; }
  void set(unsigned long m, char t) {
    rep.miles = m;
    rep.type = t;
  }

 public:
  static void* operator new(size_t size);
  static void operator delete(void* ptr, size_t size);

 private:
  static const int BLOCK_SIZE;
  static Airplane* headOfFreelist;
};

Airplane* Airplane::headOfFreelist = nullptr;
const int Airplane::BLOCK_SIZE = 512;

void* Airplane::operator new(size_t size) {
  // 在继承发生时可能会出现
  if (size != sizeof(Airplane))
    return ::operator new(size);

  Airplane* p = headOfFreelist;
  if (p)
    headOfFreelist = p->next;
  else {
    // 已空或到达链表尾端
    Airplane* newBlock =
        static_cast<Airplane*>(::operator new(BLOCK_SIZE * sizeof(Airplane)));

    // 将小块串成一个freelist
    // 跳过0是因为将要返回它，不需要设置next，
    for (int i = 1; i < BLOCK_SIZE - 1; ++i) {
      newBlock[i].next = newBlock + i + 1; 
    }
    newBlock[BLOCK_SIZE - 1].next = nullptr; 
    p = newBlock; 
    headOfFreelist = newBlock + 1; 
  }
  return p; 
}

void Airplane::operator delete(void* ptr, size_t size) {
  if (!ptr) return ; 
  if (size != sizeof(Airplane)) {
    ::operator delete(ptr); 
    return ; 
  }

  static_cast<Airplane*>(ptr)->next = headOfFreelist; 
  headOfFreelist = static_cast<Airplane*>(ptr); 
}

// TEST
int main() {

  std::cout << sizeof(Airplane) << std::endl;
  size_t constexpr N = 100; 
  Airplane* p[N] ; 

  for (int i = 0; i < N; ++i) {
    p[i] = new Airplane; 
  }

  p[1]->set(1000, 'A');
  p[2]->set(1000, 'A');
  p[3]->set(1000, 'A');
  p[4]->set(1000, 'A');
  p[5]->set(1000, 'A');
  p[6]->set(1000, 'A');
  p[7]->set(1000, 'A');
  p[8]->set(1000, 'A');

  // 间隔为8
  // 使用全局operator new则间隔32
  for (int i = 0; i < 10; ++i) {
    std::cout << p[i] << std::endl; 
  }

  for (int i = 0; i < N; ++i) {
    delete p[i]; 
  }
  return 0;
}