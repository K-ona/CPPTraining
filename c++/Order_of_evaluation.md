# Order of evaluation
<!-- https://en.cppreference.com/w/cpp/language/eval_order -->

  ```` cpp
  #include <cstdio>
  int a() { return std::puts("a"); }
  int b() { return std::puts("b"); }
  int c() { return std::puts("c"); }
  void z(int, int, int) {}
  int main() {
      z(a(), b(), c());       // all 6 permutations of output are allowed
      return a() + b() + c(); // all 6 permutations of output are allowed
  }
  ````

  Possible output:

  ```` cpp
  b
  c
  a
  c
  a 
  b
  ````

## Sequenced-before rules (since C++11)

### Definitions

**Evaluation of Expressions （表达式的计算）**

值计算（value computations）：计算表达式返回的值。 这可能涉及确定对象的身份（ glvalue ，例如，如果表达式返回对某个对象的引用）或读取先前分配给对象的值（ prvalue ，例如，如果表达式返回一个数字或某个其他值 )

副作用（initiation of side effects）：访问（读取或写入）由 volatile glvalue 指定的对象，修改（写入）对象，调用库 I/O 函数，或调用执行任何这些操作的函数。

**Ordering(顺序) 性质**

“sequenced-before”是同一线程内的 evaluation 之间的不对称、传递、成对的关系。

- A sequenced-before B, 则 evaluation of A 的结束 先于 evaluation of B 的开始。
- A is not sequenced before B 并且 B is not sequenced before A, 则下面两种情况都有可能出现：
  - A 和 B 的 evaluation 是无序的：它们可以按任何顺序执行并且可能重叠（在单个执行线程中，编译器可以生成交错 A 和 B 的 CPU 指令）
  - A 和 B 的 evaluation 是不确定的：它们可以按任何顺序执行，但不能重叠：A 将在 B 之前完成，或者 B 将在 A 之前完成。下一次 evaluation 相同的表达式时，顺序可能相反。

### Rules

1. 一个完整表达式的 `value computations` 和 `side effects` sequenced-before 下一个完整表达式的 `value computations` 和 `side effects`
2. 操作符的操作数的 `value computations` sequenced-before 整个操作符的 `value computations`
3. 函数参数、位置表达式 sequenced-before 函数体内的表达式和语句
4. 后置加减的 `value computations` sequenced-before 后置加减的 `side effects`
5. 前置加减的 `side effects` sequenced-before 前置加减的 `value computations`
6. && (and) 和 || (or)的第一个操作数的 `value computations` 和 `side effects` sequenced-before 第二个操作数的 `value computations`
7. ?: 的第一个操作数的 `value computations` 和 `side effects` sequenced-before 第二/三个操作数的 `value computations`
8. 内置赋值运算符和所有内置复合赋值运算符的`side effects`（左参数的修改） sequenced-after 左右参数的值计算（不是 `side effects`）, 并且 sequenced-before 赋值操作的 `value computations` （返回引用）
9. 逗号运算符前面的 `value computations` 和 `side effects` sequenced-before 逗号运算符后面的 `value computations` 和 `side effects`
10. 列表初始化
11. **一个函数调用和函数外部的表达式不存在 sequence before 或者 sequence after的关系**
12. 使用new时，分配函数（operator new）sequenced-before 构造器的参数（new 的参数）的evaluation（C++17起，之前不确定）
13. 从函数返回时，临时变量的拷贝初始化 sequenced-before return 语句的操作数的析构 （C++14起）
14. 在函数调用表达式中，命名函数的表达式 sequenced-before 在每个参数表达式和每个默认参数之。
15. 函数参数之间的 `value computations` 和 `side effects` 顺序不确定
16. 下标运算符  `E1[E2]` 中，E1的`value computations` 和 `side effects` sequenced-before E2的`value computations` 和 `side effects`
17. 移位运算符 E1 << E2 and E1 >> E2，E1的每一个值计算和副作用都排在E2的每一个值计算和副作用之前
18. 括号中的初始化程序中以逗号分隔的表达式列表中的每个表达式都被评估为函数调用（不确定顺序）
