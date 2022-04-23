#include <iostream>

struct my_data {
  int i; 
  double d; 
  unsigned bf1   : 10; 
  int bf2        : 23; 
  int            : 0; // fill to nearest int (10 + 23 + 31 bits)
  // int bf4        : 9; 
  int i2;  
  char c1, c2;
  std::string s; 
};

int main() {
  int align = std::alignment_of_v<my_data>; 

  int i2 = offsetof(my_data, i2);
  int d = offsetof(my_data, d);
  
  return 0;
}