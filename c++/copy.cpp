#include <windows.h>  //在Linux和Mac下要换成 unistd.h 头文件
#include <ctime>
#include <iostream>
using namespace std;

class Base {
 public:
  Base(int a = 0, int b = 0);
  Base(const Base& obj);  //拷贝构造函数
 public:
  int getCount() const { return m_count; }
  time_t getTime() const { return m_time; }

 private:
  int m_a;
  int m_b;
  time_t m_time;       //对象创建时间
  static int m_count;  //创建过的对象的数目
};

int Base::m_count = 0;
Base::Base(int a, int b) : m_a(a), m_b(b) {
  m_count++;
  m_time = time((time_t*)NULL);
}
Base::Base(const Base& obj) {  //拷贝构造函数
  this->m_a = obj.m_a;
  this->m_b = obj.m_b;
  this->m_count++;
  this->m_time = time((time_t*)NULL);
}

int main() {
  Base obj1(10, 20);
  cout << "obj1: count = " << obj1.getCount() << ", time = " << obj1.getTime()
       << endl;

  Sleep(3000);  //在Linux和Mac下要写作 sleep(3);

  Base obj2 = obj1;
  cout << "obj2: count = " << obj2.getCount() << ", time = " << obj2.getTime()
       << endl;
  return 0;
}