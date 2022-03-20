// created by Kona @VSCode
// rule 9: 优先选用别名声明而非typedef

#include <memory>
#include <vector>
#include <type_traits>
// using: alias declaration （别名声明）
// 用法示例

using ll = long long; 
typedef long long ll;  // 等价

using FP = void (*)(int, const std::string); 
typedef void (*FP)(int, const std::string); // 等价

// c++11才能直接声明别名模板
// template<typename T> 
// using VII = std::vector<T, std::allocator<T>>; 

// c++11之前
template<typename T>
struct VII
{
  typedef std::vector<T, std::allocator<T>> type; 
};


template<typename T>
class Widget {
 private:
  typename VII<T>::type vec; // 对于typedef声明的VII，需要加上关键词typename来表明该 
                             // **带依赖的型别**
  VII<T> vec; // 对于using别名声明则不用


};

int main() {
  
  Widget<int> w; 


  return 0; 
}