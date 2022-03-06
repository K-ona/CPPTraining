#include <string>
#include <iostream>

class Annotation {
 public:
  Annotation(const std::string text) 
  : value(std::move(text))
  {}
 private:
  std::string value; 

}; 


int main() {
  Annotation A("hle"); 
  // std::forward(); 
  return 0; 
}