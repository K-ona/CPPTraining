//created by Kona @VSCode
#include <iostream>
#include <memory>

class A
{
private:
    /* data */
    int x, y; 
public:
    A(/* args */);
    ~A();
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
        std::unique_ptr<A> p(new A()); 
        std::unique_ptr<A> p2 = std::make_unique<A>(); //safer about exception
        
        //std::unique_ptr<A> tmp = p; 

        
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