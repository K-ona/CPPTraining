#include <iostream>
#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr; 

struct S {
  S(int n) : mi(n) {}
  mutable int mi;
  int val;
  int f(int n) { return mi + n; }
};

struct D : public S {

  D(int n) : S(n) {}

};

int main() {

  // pointer to member data
  // type为: int S::*
  int S::*pmi = &S::mi; 
  auto pval = &S::val; 
  std::cout << type_id_with_cvr<decltype(pmi)>() << std::endl; 

  // pointer to member function
  int (S::*pf)(int) = &S::f;
  std::cout << type_id_with_cvr<decltype(pf)>() << std::endl; 

  const S s(7);
  //  s.*pmi = 10; // error: cannot modify through mutable
  // s.*pval = 10; 
  std::cout << s.*pmi << '\n';
  // std::cout << s.*pval << '\n';

  D d(7);  // base pointers work with derived object
  D* pd = &d; 
  std::cout << (d.*pf)(7) << ' ' << (pd->*pf)(8) << '\n';

  return 0; 
}