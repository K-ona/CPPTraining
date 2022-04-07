#include <mutex>
#include <atomic>

std::mutex mutex; 

double dvalue; 
int ivalue; 


int set_values(double d, int i) {
    dvalue = d; 
    std::atomic_signal_fence(std::memory_order_seq_cst);
    ivalue = i;
    return true; 
}


int main() {
  
    set_values(1.0, 2); 
}