// class condition_variable; (since C++11)

// 打算修改共享变量的线程必须
// 1. acquire a std::mutex (typically via std::lock_guard)
// 2. perform the modification while the lock is held
// 3. 在 std::condition_variable 上执行 notify_one 或 notify_all （通知不需要持有锁）
// 即使共享变量是原子的，也必须在互斥锁下进行修改，才能正确地将修改发布到等待线程。

// 任何打算等待 std::condition_variable 的线程都必须
// 1. 在用于保护共享变量的同一个互斥锁上获取 std::unique_lock<std::mutex>
//    1. check the condition, in case it was already updated and notified
//    2. 执行 wait、wait_for 或 wait_until。该操作以原子方式释放 mutex 并暂停线程的执行。
//    3. 当通知条件变量、超时到期或发生虚假唤醒时，线程被唤醒，互斥体被原子地重新获取。
//       如果唤醒是虚假的，线程应该检查条件并继续等待。


#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
 
std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;
 
void worker_thread()
{
    // Wait until main() sends data
    std::unique_lock lk(m);
    cv.wait(lk, []{return ready;});
 
    // after the wait, we own the lock.
    std::cout << "Worker thread is processing data\n";
    data += " after processing";
 
    // Send data back to main()
    processed = true;
    std::cout << "Worker thread signals data processing completed\n";
 
    // Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again (see notify_one for details)
    lk.unlock();
    cv.notify_one();
}
 

std::condition_variable cv_1;
std::mutex cv_m; // This mutex is used for three purposes:
                 // 1) to synchronize accesses to i
                 // 2) to synchronize accesses to std::cerr
                 // 3) for the condition variable cv
int i = 0;
 
void waits()
{
    std::unique_lock<std::mutex> lk(cv_m);
    std::cerr << "Waiting... \n";
    cv_1.wait(lk, []{return i == 1;});
    std::cerr << "...finished waiting. i == 1\n";
}
 
void signals()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> lk(cv_m);
        std::cerr << "Notifying...\n";
    }
    cv_1.notify_all();
 
    std::this_thread::sleep_for(std::chrono::seconds(1));
 
    {
        std::lock_guard<std::mutex> lk(cv_m);
        i = 1;
        std::cerr << "Notifying again...\n";
    }
    cv_1.notify_all();
}
 
int main()
{
    std::thread worker(worker_thread);
 
    data = "Example data";
    // send data to the worker thread
    {
        std::lock_guard lk(m);
        ready = true;
        std::cout << "main() signals data ready for processing\n";
    }
    cv.notify_one();
 
    // wait for the worker
    {
        std::unique_lock lk(m);
        cv.wait(lk, []{return processed;});
    }
    std::cout << "Back in main(), data = " << data << '\n';
 
    worker.join();



  std::thread t1(waits), t2(waits), t3(waits), t4(signals);
  t1.join(); 
  t2.join(); 
  t3.join();
  t4.join();

}