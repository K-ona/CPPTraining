#include <cstring>
#include <iostream>

class String {
 public:
  String() = default;
  String(const char* string) {
    std::cout << "created!\n";
    m_size = strlen(string);
    m_data = new char[m_size];
    memcpy(m_data, string, m_size);
  }

  String(const String& other) {
    std::cout << "Copied!\n";
    m_size = other.m_size;
    m_data = new char[m_size];
    memcpy(m_data, other.m_data, m_size);
  }

  String(String&& other) noexcept {
    std::cout << "Moved!\n";
    m_size = other.m_size;
    m_data = other.m_data;

    other.m_size = 0;
    other.m_data = nullptr;
  }

  String& operator=(String&& other) noexcept {
    if (m_data != other.m_data) {

      delete[] m_data; 

      std::cout << "Moved!\n";
      m_size = other.m_size;
      m_data = other.m_data;

      other.m_size = 0;
      other.m_data = nullptr;
    }
    return *this; 
  }

  ~String() {
    if (m_data != nullptr) 
      std::cout << "Destroyed\n";
    delete[] m_data;
  }

  void print() {
    for (size_t i = 0; i < m_size; ++i) {
      std::cout << m_data[i];
    }
    std::cout << "\n";
  }

 private:
  char* m_data;
  size_t m_size;
}; 

class Entity {
 public:
  Entity(const String& name): m_name(name) {} 
  Entity(String&& name): m_name(std::move(name)) {} 
 
  void print_name() {
    m_name.print(); 
  }
 private:
  String m_name; 
};

void func(String a) {
  a.print(); 
}


int main() {
  String tmp = "ll"; 
  func(tmp);
  func("111"); 

  Entity entity("Kona"); 
  entity.print_name(); 

  String string = "Hello"; 
  String dest;
  dest = std::move(string); 

  return 0;
}