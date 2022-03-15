#include <iostream>
#include <memory>

// 对于NULL，通常实现是整型的0值（int, long, long long等）
// c++只会在只能使用指针的语境中把0解释为空指针

// 在指针类型与整型重载时可能会出现问题

void f(int); 
void f(bool); 
void f(void*); 

// f(0);   调用 f(int)
// f(NULL);   一般调用 f(int)，不可能调用f(void*)

// nullptr的优点在于 它不具有整型型别，也不具有指针型别，但是可以理解成一个任意型别的指针
// nullptr的实际类型是std::nullptr_t; std::nullptr_t可以**隐式转换到所有的裸指针型别**

// f(nullptr); 会调用 f(void*)版本

// 另一个优点：一个变量与0比较时，该变量是整型还是指针型别一眼不得而知，
// 而如果一个变量与nullptr比较，则不会有歧义

// 最大的优势在于模板编写，0、NULL都会被推导成整型，而nullptr被推导成std::nullptr_t
// 而后又被隐式转换成对应指针型别


void f2(std::shared_ptr<int>) {

}

void f3(std::unique_ptr<int>) {

}

void f4(int *) {

}

template<typename Function, 
         typename Para>
decltype(auto) call(Function f, Para para) {
  f(para); 
}

int main() {

  nullptr; 

  std::nullptr_t a; 

  f2(0); // 合法
  f3(NULL); // 合法
  f4(nullptr); 

  // call(f2, 0); // error: could not convert 'para' from 'int' to 'std::shared_ptr<int>'
  // call(f3, NULL); // error: could not convert 'para' from 'long long int' to 'std::unique_ptr<int>'
  call(f4, nullptr); 

  return 0; 
}