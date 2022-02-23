//created by Kona @VSCode
#include <iostream>
#include <memory>
#include <vector>

class A
{
private:
    /* data */
    int x, y; 
public:
    A(int a, int b): x(a), y(b) {};
    A(); 
    ~A(); 
    void print() {
        std::cout << x << " " << y << std::endl; 
    }
};

A::A(/* args */)
{
    std::cout << "construct" << std::endl; 
}

A::~A()
{
    std::cout << "deconstruct" << std::endl; 
}


int main()
{
    std::ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */
    // A a;

    {
        std::unique_ptr<A> p(new A(1, 2)); 
        std::unique_ptr<A> p2 = std::make_unique<A>(3, 4); //safer about exception
        std::vector<std::unique_ptr<A>> V; 
        V.push_back(std::move(p)); 
        V.push_back(std::move(p2)); 
        // V.push_back(std::move(p2)); 
        V[0]->print(); 
        V[1]->print(); 
        std::cout << p.get() << " " << p2.get() << std::endl;
        // p.release(); 
        // p->print(); 
        
        // error: 不存在从 "A *" 转换到 "std::unique_ptr<A, std::default_delete<A>>" 的适当构造函数
        // std::unique_ptr<A> tmp = new A; 
        
        // error: 无法引用 函数 "std::unique_ptr<_Tp, _Dp>::unique_ptr(const std::unique_ptr<_Tp, _Dp> &) [其中 _Tp=A, _Dp=std::default_delete<A>]" 
        // std::unique_ptr<A> tmp = p; 
        
        std::unique_ptr<A[]> p3 = std::make_unique<A[]>(10); 

        std::cout << "test: " << std::endl; 
        auto A1 = new A(); 
        std::shared_ptr<A> pa1(A1); 
        std::cout << "test end" << std::endl; 
        
        std::shared_ptr<A> q(new A()); // low efficiency, for the allocation of control block
        std::weak_ptr<A> weakp; 
        {
            std::shared_ptr<A> q1 = std::make_shared<A>(); // 
            std::cout << "q.count == " << q.use_count() << std::endl; 
            q = q1;  //ok
            std::cout << "q1.count == " << q1.use_count() << std::endl; 
            std::cout << "q.count == " << q.use_count() << std::endl; 
            weakp = q1; 
            std::cout << "weakp.count == " << weakp.use_count() << std::endl; 
            std::cout << "q.count == " << q.use_count() << std::endl;  
        }
        std::cout << "get out of scope" << std::endl; 
        std::cout << "weakp.count == " << weakp.use_count() << std::endl; 
        std::cout << "q.count == " << q.use_count() << std::endl;  
    }


    return 0;
}