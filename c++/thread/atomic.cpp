#include <mutex>

std::mutex mutex; 

double dvalue; 
int ivalue; 


int set_values(double d, int i) {
    std::lock_guard<std::mutex> lock(::mutex); 
    static int si = 0; 
    ++si;
    dvalue = d; 
    ivalue = i;
    return si; 
}

int main() {
  
    set_values(1.0, 2); 
}