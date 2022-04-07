#pragma once
#include <iostream>

namespace KonaImpl {

  // Base exception
  class exception {
   public:
    exception() noexcept {}
    exception(const exception&) = default;
    exception& operator=(const exception&) = default;
    exception(exception&&) = default;
    exception& operator=(exception&&) = default;
    
    virtual ~exception() noexcept {}

    virtual const char* what() const noexcept { return nullptr; };
  };

  class runtime_error: public exception {
   public: 
    const char* m_message; 
    runtime_error(const char* message): m_message(message) {}
    virtual ~runtime_error() noexcept {}

    virtual const char* what() const noexcept {
      return m_message; 
    }
  }; 

  class out_of_range: public runtime_error{
   public:
    explicit
    out_of_range(const char* message) : runtime_error(message) {}
    virtual ~out_of_range() noexcept { std::cerr << "what(): " << m_message << std::endl; }
    virtual const char* what() const noexcept { return m_message; }
  };

  class invalid_argument: public runtime_error{
   public:
    explicit
    invalid_argument(const char* message) : runtime_error(message) {}
    virtual ~invalid_argument() noexcept { std::cerr << "what(): " << m_message << std::endl; }
    virtual const char* what() const noexcept { return m_message; }
  };
  


};
