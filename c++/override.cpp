#include <iostream>
#include <vector>

using std::cout;
using std::endl;

// #define TEST_OVERRIDE

#ifdef TEST_OVERRIDE
// 被改写的虚函数需要饰词相同
class Base {
 public:
  virtual void foo() const { cout << "Base::foo()" << endl; }
  virtual void goo() volatile { cout << "Base::goo()" << endl; }
  virtual void hoo() & { cout << "Base::goo()" << endl; }
// 注意：与 cv-qualification 不同，ref-qualification 不会更改 this 指针的属性：
// 在 rvalue ref-qualified 函数中，*this 仍然是一个左值表达式。
};

class Derived : public Base {
 public:
  void foo() const override { cout << "Derived::foo()" << endl; }
  virtual void goo() volatile override { cout << "Derived::goo()" << endl; }
  virtual void hoo() & override { cout << "Base::goo()" << endl; }
};
#endif

struct Base
{
    virtual void foo();
};
 
struct A : Base
{
    void foo() final; // Base::foo is overridden and A::foo is the final override
    void bar() final; // Error: bar cannot be final as it is non-virtual
};
 
struct B final : A // struct B is final
{
    void foo() override; // Error: foo cannot be overridden as it is final in A
};
 
struct C : B // Error: B is final
{
};

int main() {
  Base* a = new Base();
  a->foo();
  Base* b = new Derived();
  b->foo();
  return 0;
}