#include <thread>

// 1. 传递函数指针构造 std::thread 对象
void do_some_work();
std::thread my_thread(do_some_work);

// 2. 传入重载 operator() 的函数对象 (funtor), 构造 std::thread 对象

class background_task {
 public:
  void operator()() const {
    // do_something();
    // do_something_else();
  }
};

background_task f;
std::thread my_thread(f);

// 需要注意 “最令人头痛的c++语法解析” : 优先解析为声明

std::thread my_thread_1(background_task()); 
// 传入临时对象时，编译器将其解析为一个函数声明: std::thread my_thread_1(background_task (*)())
// 解决方案: 
std::thread my_thread_2((background_task())); // 1
std::thread my_thread_3{background_task()};   // 2


// 3. 传入 lambda 函数对象, 构造 std::thread 对象
// lambda 可以视为 可以捕获局部变量的局部函数对象
std::thread my_thread([] {
  // do_something();
  // do_something_else();
});

// 线程启动后是要等待线程结束，还是让其自主运行。当 std::thread 对象销毁之前还没有做出决定，程序就会
// 终止( std::thread 的析构函数会调用 std::terminate() )

// 同时不等待线程汇入，需保证线程访问数据的有效性，如线程函数持有局部变量的 指针或引用

struct func {
  int& i;
  func(int& i_) : i(i_) {}
  void operator()() {
    for (unsigned j = 0; j < 1000000; ++j) {
      // do_something(i);  // 1 潜在访问隐患：悬空引用 导致未定义行为
    }
  }
};

void oops() {
  int some_local_state = 0;
  func my_func(some_local_state);
  std::thread my_thread(my_func);
  my_thread.detach();  // 2 不等待线程结束
}  // 3 新线程可能还在运行

// 常用解决方案：将数据复制到线程中 或 通过 join() 确保线程在主函数完成之前结束


// 2.1.3 特殊情况下的等待
// 创建线程后抛出异常，导致 join() 被条跳过

// 使用 try catch 
struct func;  // 定义在代码2.1中
void ff_1() {
  int some_local_state = 0;
  func my_func(some_local_state);
  std::thread t(my_func);
  try {
    // do_something_in_current_thread();
  } catch (...) {
    t.join();  // 1
    throw;
  }
  t.join();  // 2
}

// 使用“资源获取即初始化方式”(RAII，Resource Acquisition Is Initialization)
// 提供一个类，在析构函数中使用join()。

class thread_guard {
  std::thread& t;

 public:
  explicit thread_guard(std::thread& t_) : t(t_) {}
  ~thread_guard() {
    if (t.joinable())  // 1
    {
      t.join();  // 2
    }
  }
  thread_guard(thread_guard const&) = delete;  // 3
  thread_guard& operator=(thread_guard const&) = delete;
};

struct func;  // 定义在代码2.1中
void ff_2() {
  int some_local_state = 0;
  func my_func(some_local_state);
  std::thread t(my_func);
  thread_guard g(t);
  // do_something_in_current_thread();
}  // 4

// 运行到4时，thread_guard 对象 g 将被析构，线程 t 将在析构函数中被 join()
// 即使do_something_in_current_thread抛出一个异常，这个销毁依旧会发生

// 2.1.4 后台运行线程
// 使用detach()会让线程在后台运行，这就意味着与主线程不能直接交互。
// 分离线程通常称为守护线程(daemon threads)。

// 代码2 .4 使用分离线程处理文档 
void edit_document(std::string const& filename) {
  open_document_and_display_gui(filename);
  while (!done_editing()) {
    user_command cmd = get_user_input();
    if (cmd.type == open_new_document) {
      std::string const new_name = get_filename_from_user();
      std::thread t(edit_document, new_name);  // 1
      t.detach();                              // 2
    } else {
      // process_user_input(cmd);
    }
  }
}

// 2.2 传递参数
// 向可调用对象或函数传递参数很简单，只需要将这些参数作为 std::thread 构造函数的附加参数即可。
// 需要注意的是，这些参数会拷贝至新线程的内存空间中(同临时变量一样), 即使函数的形参是引用形式

void f_2_2(int i, std::string const& s); 
void oops(int some_param) {
  char buffer[1024];  // 1
  sprintf(buffer, "%i", some_param);
  std::thread t(f_2_2, 3, buffer);  // 2 : buffer 隐式转换到std::string 可能发生在 std::thread 的构造函数后
  // std::thread t(f_2_2, 3, std::string(buffer));  // 解决方案：使用 先手动转换
  t.detach();
}

void update_data_for_widget(widget_id w, widget_data& data);  // 1
void oops_again(widget_id w) {
  widget_data data;
  std::thread t(update_data_for_widget, w, data);  // 2
  display_status();
  t.join();
  process_widget_data(data);
}

// s 需要具备 const 属性 否则编译错误：尝试使用线程更新引用传递的数据结构
// 内部代码会将拷贝的参数  **以右值的方式进行传递** ，这是为了那些只支持移动的类型，
// 而后会尝试以右值为实参调用update_data_for_widget。
// 但因为函数期望的是一个非常量引用作为参数(而非右值)，所以会在编译时出错。

// 解决方案：使用 std::ref
std::thread t(update_data_for_widget,w,std::ref(data));

// 调用成员函数

class X {
 public:
  void do_lengthy_work(int);
};
X my_x;
int num(0);
std::thread t(&X::do_lengthy_work, &my_x, num);

