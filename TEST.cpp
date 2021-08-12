//created by Kona @VSCode
#include <iostream>
#include <vector>
#include <string>
#include <map>

// #define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::map;
using std::vector;
using std::string;
using std::cout;
using std::endl;

int main() {
    std::ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */

        // generic lambda, operator() is a template with two parameters
    auto glambda = [](auto a, auto&& b) { return a < b; };
    bool b = glambda(3, 3.14); // ok
 
    // generic lambda, operator() is a template with one parameter
    auto vglambda = [](auto printer) {
        return [=](auto&&... ts) // generic lambda, ts is a parameter pack
        { 
            printer(std::forward<decltype(ts)>(ts)...);
            return [=] { printer(ts...); }; // nullary lambda (takes no parameters)
        };
    };
    auto p = vglambda([](auto v1, auto v2, auto v3) { std::cout << v1 << v2 << v3; });
    auto q = p(1, 'a', 3.14); // outputs 1a3.14
    q();                      // outputs 1a3.14

    return 0;
}