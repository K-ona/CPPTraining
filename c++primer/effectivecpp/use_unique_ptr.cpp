#include <memory>
#include <iostream>

using std::cout; 

class Investment {

public:
 virtual ~Investment(); 
};

class Stock:
  public Investment {

}; 

class Bond:
  public Investment {

}; 

class RealEstate:
  public Investment {

}; 

template<typename... Ts>
auto makeInvestment(Ts&&... params) {
  auto dlInvmt = [](Investment* pInvestment) {
    // log
    delete pInvestment; 
  }; 

  std::unique_ptr<Investment, decltype(dlInvmt)> pInv(nullptr, dlInvmt); 
  
  if (...) { // 应创建一个Stock对象
    pInv.reset(new Stock(std::forward(params)...)); 
  } else if (...) { // 应创建一个Bond对象
    pInv.reset(new Bond(std::forward(params)...)); 
  } else if (...) { // 应创建一个RealEstate对象
    pInv.reset(new RealEstate(std::forward(params)...)); 
  }
  return pInv; 
}

int main() {
  
  
  return 0; 
}