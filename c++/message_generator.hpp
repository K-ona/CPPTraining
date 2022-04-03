#ifndef message_body
# error message_body is not defined
#endif

#ifndef message_name
# error message_name is not defined
#endif

struct message_name {
  #undef field_variable
  #define field_variable(type, name, ...) type name = {__VA_ARGS__};

  message_body
};

inline std::ostream& operator<<(std::ostream& os, const message_name& message) {

#undef field_variable
#define field_variable(type, name, ...) os << #name << ": " << message.name << std::endl;
  message_body
  return os;
}

#undef message_body
#undef message_name