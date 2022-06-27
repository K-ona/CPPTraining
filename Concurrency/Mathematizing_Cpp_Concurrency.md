# Mathematizing C++ Concurrency

## Introduction

C 语言和 C++语言 的标准由于历史原因，没有覆盖到并发编程的所有需求。

这里的关键问题在于 **硬件和编译器优化引起的多处理器 松弛内存（relaxed-memory）行为**
编程语言的设计包含了**性能**和**可用性**的权衡
