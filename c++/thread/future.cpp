// template< class T > class future;        (1)	(since C++11)
// template< class T > class future<T&>;    (2)	(since C++11)
// template<>          class future<void>;  (3)	(since C++11)

// std::future提供了一个访问异步操作结果的机制
// 1. 通过std::async, std::packaged_task, std::promise等方法可以创建一个异步操作, 
// 并向异步操作的创建者返回一个std::future对象
// 2. 然后，异步操作的创建者可以使用各种方法从 std::future 中查询、等待或提取值。
// 如果异步操作尚未提供值，这些方法可能会阻塞。
// 3. 当异步操作准备好向创建者发送结果时，它可以通过修改 链接到创建者的 std::future 的共享状态
// （例如 std::promise::set_value）来做到这一点。

// 注意，std::future 引用了不与任何其他异步返回对象共享的共享状态（与 std::shared_future 相对）

#include <thread>
#include <future>
#include <iostream>
#include <string>
#include <chrono>
 
std::string time() {
    static auto start = std::chrono::steady_clock::now();
    std::chrono::duration<double> d = std::chrono::steady_clock::now() - start;
    return "[" + std::to_string(d.count()) + "s]";
}

int main() {

     // future from a packaged_task
    std::packaged_task<int()> task([]{ return 7; }); // wrap the function
    std::future<int> f1 = task.get_future();  // get a future
    std::thread t(std::move(task)); // launch on a thread
 
    // future from an async()
    std::future<int> f2 = std::async(std::launch::async, []{ return 8; });
 
    // future from a promise
    std::promise<int> p;
    std::future<int> f3 = p.get_future();
    std::thread( [&p]{ p.set_value_at_thread_exit(9); }).detach();
 
    std::cout << "Waiting..." << std::flush;
    f1.wait();
    f2.wait();
    f3.wait();
    std::cout << "Done!\nResults are: "
              << f1.get() << ' ' << f2.get() << ' ' << f3.get() << '\n';
    t.join();

    using namespace std::chrono_literals;
    {
        std::cout << time() << " launching thread\n";
        std::future<int> f = std::async(std::launch::async, []{
            std::this_thread::sleep_for(1s);
            return 7;
        });
        std::cout << time() << " waiting for the future, f.valid() == "
                  << f.valid() << "\n";
        int n = f.get();
        std::cout << time() << " future.get() returned with " << n << ". f.valid() = "
                  << f.valid() << '\n';
    }
 
    {
        std::cout << time() << " launching thread\n";
        std::future<int> f = std::async(std::launch::async, []{
            std::this_thread::sleep_for(1s);
            return true ? throw std::runtime_error("7") : 7;
        });
        std::cout << time() << " waiting for the future, f.valid() == "
                  << f.valid() << "\n";
        try {
            int n = f.get();
            std::cout << time() << " future.get() returned with " << n
                      << " f.valid() = " << f.valid() << '\n';
        } catch(const std::exception& e) {
            std::cout << time() << " caught exception " << e.what()
                      << ", f.valid() == " << f.valid() << "\n";
        }
    }
}