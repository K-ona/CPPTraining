[[https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#cp200-use-volatile-only-to-talk-to-non-c-memory]]

**Use volatile only to talk to non-C++ memory**
**In C++, unlike in some other languages, volatile has nothing to do with synchronization.**

volatile is used to refer to objects that are shared with "non-C++" code
or hardware that does not follow the C++ memory model.

const volatile long clock;

这描述了由时钟电路不断更新的寄存器。时钟是易失的，因为它的值发生变化 与c++程序无关。

例如，两次读取时钟通常会产生两个不同的值，因此优化器最好不要优化此代码中的第二次读取：

clock is const because the program should not try to write to clock.

除非您正在编写直接操作硬件的最低级别代码，否则不要使用volatile

[[Usually C++ code receives volatile memory that is owned elsewhere (hardware or another language):]]

int volatile* vi = get_hardware_memory_location();
  note: we get a pointer to someone else's memory here
  volatile says "treat this with extra respect"

有时 C++ 代码会通过故意转义指针来分配易失性内存并与“其他地方”（硬件或其他语言）共享它：
static volatile long vl;
please_use_this(&vl);   // escape a reference to this to "elsewhere" (not C++)

volatile 局部变量几乎总是错误的——如果它们是短暂的，它们如何与其他语言或硬件共享？出于同样的原因，这同样适用于成员变量。

void f()
{
    volatile int i = 0; // bad, volatile local variable
    // etc.
}

class My_type {
    volatile int i = 0; // suspicious, volatile member variable
    // etc.
};

[[https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#Rconc-volatile]]

Don't try to use volatile for synchronization

**在 C++ 中，与其他一些语言不同，volatile 不提供原子性，不在线程之间同步，也不阻止指令重新排序（无论是编译器还是硬件）。它根本与并发无关。**

Example, bad:

int free_slots = max_slots; // current source of memory for objects

Pool* use()
{
    if (int n = free_slots--) return &pool[n];
}

Here we have a problem: This is perfectly good code in a single-threaded program, but have two threads execute this and there is a race condition on free_slots so that two threads might get the same value and free_slots. That's (obviously) a bad data race, so people trained in other languages might try to fix it like this:

volatile int free_slots = max_slots; // current source of memory for objects

Pool* use()
{
    if (int n = free_slots--) return &pool[n];
}
This has no effect on synchronization: The data race is still there!

The C++ mechanism for this is atomic types:

atomic<int> free_slots = max_slots; // current source of memory for objects

Pool* use()
{
    if (int n = free_slots--) return &pool[n];
}

Now the -- operation is atomic, rather than a read-increment-write sequence where another thread might get in-between the individual operations.

Alternative
Use atomic types where you might have used volatile in some other language. Use a mutex for more complicated examples.
