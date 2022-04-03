#include <iostream>
#include <string>

#define message_name foo
#define message_body                        \
  field_variable(int, bar, 1)               \
  field_variable(std::string, name, "kona") \
  field_variable(double, pi)                \
  //


#include "message_generator.hpp"

int main() {

  foo test; 
  std::cout << test; 
  test.pi = 3.14; 

  return 0;
}