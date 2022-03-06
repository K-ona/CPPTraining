#include <iostream>

extern int x; 
int w = 123; 

int fun(const char *s) {
    std::cout << s << std::endl; 
    std::cout << "x == " << x << std::endl; 
    return 1; 
}

static void print_z() {

}