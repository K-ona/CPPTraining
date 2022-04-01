#pragma once

#include <string>
#include <iostream>

#ifdef DEBUG_MODE
void DEBUG(std::string s) {
  std::cout << s << std::endl;
}
#endif

#ifndef DEBUG_MODE
void DEBUG(std::string s) {
}
#endif