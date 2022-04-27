# 内存模型和原子操作

- C++ 内存模型
- 原子类型
- 如何使用原子类型
- 使用原子操作同步线程

C++标准中有一个重要特性常被开发者所忽略，就是**多线程(感知)内存模型**，内存模型定义了基本部件应该如何工作。那为什么大多数开发者都没有注意到呢？当使用互斥量保护数据和条件变量，或者信号时，对于互斥量*为什么*能起到这样作用，大多数人并不会关心。只有试图去“接触硬件”，才能详尽的了解到内存模型是如何作用的。

==C++是系统级别的编程语言，标准委员会的目标是不需要比C++还要底层的高级语言。== C++应该向程序员提供足够的灵活性，无障碍的去做他们想要做的事情。需要时，也可以“接触硬件”。原子类型和原子操作就可以“接触硬件”，并提供底层同步操作，通常会将指令数缩减到1~2个CPU周期。

## 5.1 内存模型

内存模型一方面是内存布局，另一方面是并发

### 5.1.1 对象和内存位置

C++程序中数据都是由对象构成，对象仅仅是对C++数据构建块的声明，C++标准定义类对象为 ==“存储区域”== ，但对象还是可以将自己的特性赋予其他对象。

这里有四个需要牢记的原则：

1. 每个变量都是对象
2. 每个对象至少占有一个内存位置。
3. 基本类型都有确定的内存位置(无论类型大小如何，即使他们是相邻的，或是数组的一部分)。
4. 相邻位域是相同内存中的一部分。

==这些在并发中有什么作用？==

### 5.1.2 对象、内存位置和并发

这部分对于C++的多线程来说至关重要。当两个线程访问不同的内存位置时，不会存在任何问题，当两个线程访问同一个内存位置就要小心了。如果线程不更新数据，只读数据不需要保护或同步。当线程对内存位置上的数据进行修改，就可能会产生条件竞争。

为了避免条件竞争，线程就要以一定的顺序执行。第一种方式，使用互斥量来确定访问的顺序。当同一互斥量在两个线程同时访问前锁住，那么在同一时间内就只有一个线程能够访问对应的内存位置。另一种是使用原子操作决定两个线程的访问顺序，当多个线程访问同一个内存地址时，对每个访问者都需要设定顺序。

如果不规定对同一内存地址访问的顺序，那么访问就不是原子的。当两个线程都是“写入者”时，就会产生数据竞争和未定义行为。

未定义的行为是C++中的黑洞，当程序对同一内存地址中的数据访问存在竞争，可以使用原子操作来避免未定义行为。当然，这不会影响竞争的产生——原子操作并没有指定访问顺序——而原子操作会把程序拉回到定义行为的区域内。

### 5.1.3 修改顺序

如果对象不是原子类型(将在5.2节详述)，必须确保有足够的同步操作，确定线程都遵守了修改顺序。当不同线程在不同序列中访问同一个值时，可能就会遇到数据竞争或未定义行为(详见5.1.2节)。如果使用原子操作，编译器就有责任去做同步。

因为当线程按修改顺序访问一个特殊的输入，所以投机执行是不允许的。 **之后的读操作必须由线程返回新值，并且之后的写操作必须发生在修改顺序之后。** 虽然，所有线程都需要遵守程序中每个非独立对象的修改顺序，但==没有必要遵守在独立对象上的操作顺序==。在5.3.3节中会有更多关于不同线程间操作顺序的内容。所以，什么是原子操作？怎样规定顺序？

## 5.2 原子操作和原子类型

原子操作是个不可分割的操作。系统的所有线程中，不可能观察到原子操作完成了一半。如果读取对象的加载操作是原子的，那么这个对象的所有修改操作也是原子的，所以加载操作得到的值要么是对象的初始值，要么是某次修改操作存入的值。

另一方面，非原子操作可能会被另一个线程观察到只完成一半。如果这个操作是一个存储操作，那么其他线程看到的值，可能既不是存储前的值，也不是存储的值。如果非原子操作是一个读取操作，可能先取到对象的一部分，然后值被另一个线程修改，然后它再取到剩余的部分，所以它取到的既不是第一个值，也不是第二个值。这就构成了数据竞争(见5.1节)，出现未定义行为。

### 5.2.1 标准原子类型

标准原子类型定义在头文件 ```<atomic>``` 中。这些类型的操作都是原子的，语言定义中只有这些类型的操作是原子的，也可以用互斥锁来模拟原子操作

它们(几乎)都有一个 ```is_lock_free()```成员函数，这个函数可以让用户查询某原子类型的操作是直接用的原子指令( ```x.is_lock_free()``` 返回 true )，还是内部用了一个锁结构( ```x.is_lock_free()``` 返回 false )。

原子操作可以替代互斥量，来完成同步操作。如果操作内部使用互斥量实现，那么不可能有性能的提升。所以要对原子操作进行实现，最好使用不基于互斥量的实现。

宏都有 ```ATOMIC_BOOL_LOCK_FREE , ATOMIC_CHAR_LOCK_FREE , ATOMIC_CHAR16_T_LOCK_FREE , ATOMIC_CHAR32_T_LOCK_FREE， ATOMIC_WCHAR_T_LOCK_FREE ， ATOMIC_SHORT_LOCK_FREE , ATOMIC_INT_LOCK_FREE , ATOMIC_LONG_LOCK_FREE , ATOMIC_LLONG_LOCK_FREE 和 ATOMIC_POINTER_LOCK_FREE``` 。它们指定了内置原子类型的无锁状态和无符号对应类型(LLONG对应long long，POINTER对应所有指针类型)。如果原子类型**不是无锁结构，那么值为0**。如果原子类型是**无锁结构，那么值为2**。如果原子类型的**无锁状态在运行时才能确定，那么值为1**。

只有 ```std::atomic_flag``` 类型不提供 ```is_lock_free()``` 。该类型是一个简单的布尔标志，并且在这种类型上的操作都是无锁的。

对于 std::atomic<T> 模板，使用相应的T类型去特化模板的方式，要好于使用别名的方式。

通常，标准原子类型不能进行拷贝和赋值，它们没有拷贝构造函数和拷贝赋值操作符。但是，可以隐式转化成对应的内置类型，所以这些类型依旧支持赋值，可以使用 ```load()``` 和 ```store()``` 、 ```exchange()``` 、 ```compare_exchange_weak()``` 和 ```compare_exchange_strong()``` 。

它们都支持复合赋值符：+=, -=, *=, |= 等等。并且使用整型和指针的特化类型还支持++和--操作。当然，这些操作也有功能相同的成员函数所对应：```fetch_add()```, ```fetch_or()```等等。赋值操作和成员函数的返回值，要么是存储值(赋值操作)，要么是操作值(命名函数)，这就能避免赋值操作符返回引用。

```std::atomic<>``` 类模板不仅仅是一套可特化的类型，作为原发模板也可以使用自定义类型创建对应的原子变量。因为是通用类模板，操作限制为 ```load()``` ， ```store()```(赋值和转换为用户类型)，`exchange()` ， `ompare_exchange_weak()` 和 `compare_exchange_strong()` 。

每种函数类型的操作都有一个==内存序参数==，这个参数可以用来指定存储的顺序。5.3节中，会对存储顺序选项进行详述。

现在，只需要知道操作分为三类：

1. Store操作，可选如下内存序： `memory_order_relaxed , memory_order_release , memory_order_seq_cst`
2. Load操作，可选如下内存序：`memory_order_relaxed , memory_order_consume , memory_order_acquire ,memory_order_seq_cst`
3. Read-modify-write(读-改-写)操作，可选如下内存序： `memory_order_relaxed , memory_order_consume ,memory_order_acquire , memory_order_release , memory_order_acq_rel , memory_order_seq_cst`

### 5.2.2 `std::atomic_flag`

`std::atomic_flag` 是最简单的原子类型，这个类型的对象可以在两个状态间切换：设置和清除。

`std::atomic_flag` 类型的对象必须被ATOMIC_FLAG_INIT初始化。初始化标志位是“清除”状态。这里没得选
择，这个标志总是初始化为“清除”：

  ``` cpp
  std::atomic_flag f = ATOMIC_FLAG_INIT;
  ```

当标志对象已初始化，只能做三件事情：销毁，清除或设置(查询之前的值)

`clear()`和`test_and_set()`成员函数可以指定好内存顺序。`clear()`是一个存储操作，所以不能有`memory_order_acquire`或`memory_order_acq_rel`语义，但`test_and_set()`是一个“读-改-写”操作，可以应用于任何内存顺序。每一个原子操作，默认的内存序都是`memory_order_seq_cst`。

例如：

  ``` cpp
  f.clear(std::memory_order_release); // 1
  bool x=f.test_and_set(); // 2
  ```

不能拷贝构造 `std::atomic_flag` 对象，不能将一个对象赋予另一个 `std::atomic_flag` 对象。这不是`std::atomic_flag` 特有的属性，而是所有原子类型共有的属性。原子类型的所有操作都是原子的，而赋值和拷贝调用了两个对象，这就就破坏了操作的原子性。这样的话，拷贝构造和拷贝赋值都会将第一个对象的值进行读取，然后再写入另外一个。对于两个独立的对象，这里就有两个独立的操作了，合并这两个操作必定是不原子的。因此，操作就不被允许。

代码5.1 使用 std::atomic_flag 实现自旋锁

  ```` cpp
  class spinlock_mutex
  {
    std::atomic_flag flag;
  public:
    spinlock_mutex():
    flag(ATOMIC_FLAG_INIT)
    {}
    void lock()
    {
      while(flag.test_and_set(std::memory_order_acquire));
    }
    void unlock()
    {
      flag.clear(std::memory_order_release);
    }
  };
  ````

### 5.2.3 `std::atomic< bool >`

最基本的原子整型类型就是 `std::atomic<bool>` ，它有着比 `std::atomic_flag` 更加齐全的布尔标志特性。虽然不能拷贝构造和拷贝赋值，但可以使用非原子的bool类型进行构造，所以可以初始化为true或false，并且可以从非原子bool变量赋值给 `std::atomic<bool>`:

  ``` cpp
  std::atomic<bool> b(true);
  b=false;
  ```

另外，非原子bool类型的赋值操作不同于通常的操作(转换成对应类型的引用，再赋给对应的对象)：它返回一个bool值来代替指定对象。

原子类型中的另一种模式：通过返回值(返回相关的非原子类型)完成赋值。如果原子变量的引用返回了，任何依赖与这个赋值结果的代码都需要显式加载。问题是，结果可能会被其他线程修改。通过返回非原子值进行赋值的方式，可以避免多余的加载过程，并得到实际存储的值。

虽然有内存序的指定，但使用`store()`写入(`true`或`false`)还是好于 `std::atomic_flag` 中的 `clear()`。同样，`test_and_set()`也可以替换为更加通用的 `exchange()`，`exchange()` 允许使用新选的值替换已存储的值，并且会自动检索原始值。 `std::atomic<bool>` 也支持对值的(不可修改)查找，其会将对象隐式的转换为普通的bool值，或显示的调用`load()`来完成。`store()`是一个存储操作，而`load()`是一个加载操作，`exchange()`是一个“读-改-写”操作：

  ``` cpp
  std::atomic<bool> b;
  bool x=b.load(std::memory_order_acquire);
  b.store(true);
  x=b.exchange(false, std::memory_order_acq_rel);
  ```

 `std::atomic< bool >` 还介绍了一种新的存储方式：当前值与预期值一致时，存储新值的操作。

**存储一个新值(或旧值)取决于当前值**

这种新型操作叫做“比较/交换”，它的形式表现为`compare_exchange_weak()`和`compare_exchange_strong()`

“比较/交换”操作是原子类型编程的基石，它 (原子地) 比较原子变量的当前值和期望值，当两值相等时，存储所提供值。当两值不等，期望值就会被更新为原子变量中的值。当原子变量的值被成功存储时，返回true，否则返回false。

对于compare_exchange_weak()，当原始值与预期值一致时，存储也可能会不成功（返回false）。称为“伪失败”(spurious failure)，这最可能发生在缺少单条CAS操作(compare-and-swap/set 指令)的机器上, 即处理器不能保证这个操作能够原子地完成时。（可能因为线程的操作执行到必要操作的中间时被切换，并且另一个线程将会被操作系统调度，这里线程数多于处理器数量）

因为`compare_exchange_weak()`可以伪失败，所以通常会配合一个循环使用：(尽管如此，`compare_exchange_weak()` 的效率仍比 `compare_exchange_strong()`)

  ``` cpp
  bool expected=false;
  extern atomic<bool> b; // 设置些什么
  while(!b.compare_exchange_weak(expected,true) or !expected)
    ;
  ```

如果只想要不管 `atomic` 变量的初始值并改变它的变量值，对 `expected` 的更新将会变更有用；经历每次循环的时候， `expected` 都会重新加载，所以当没有其他线程同时修改 `expected` 时，循环中对`compare_exchange_weak()` 或 `compare_exchange_strong()`的调用都会在下一次(第二次)成功。

如果值很容易存储，使用`compare_exchange_weak()`能更好的避免一个双重循环的执行，即使`compare_exchange_weak()`可能会“伪失败”。另一方面，如果值的存储本身非常耗时，当期望值不变时，使用`compare_exchange_strong()`可以避免对值的重复计算。

对于 `std::atomic<bool>` 这些都不重要——毕竟只有两种值——但是对于其他的原子类型影响就比较大了。

“compare/exchange”另一点不同的是，它拥有对两个内存序的参数进行操作的能力，这就允许内存序语义在成功和失败的例子中有所不同。可能成功时使用`memory_order_acq_rel`，而失败时使用`memory_order_relaxed`。失败的“compare/exchange”将不会进行存储，所以“compare/exchange”操作不能拥有`meory_order_release`或`memory_order_acq_rel`。因此，不保证这些值能作为失败的内存序，也不能提供比成功内存序更加严格的失败内存序，当`memory_order_acquire`或`memory_order_seq_cst`作为失败时的内存序时，也要为成功时指定内存序。如果没有指定失败语序，那就和成功的语序一样了，除了release部分的顺序：`memory_order_release`变成`memory_order_relaxed`，并且`memoyr_order_acq_rel`变成`memory_order_acquire`。如果都不指定，默认顺序将为`memory_order_seq_cst`。下面对`compare_exchange_weak()`的两次调用是等价的：

  ```` cpp
  bool expected;
  b.compare_exchange_weak(expected, true,
    memory_order_acq_rel, memory_order_acquire);
  b.compare_exchange_weak(expected, true, memory_order_acq_rel);
  ````

`std::atomic<bool>` 和 `std::atomic_flag` 的不同之处在于， `std::atomic<bool>` 可能不是无锁的。为了保证操作的原子性，其实现中可能需要内置的互斥量。特殊情况时，可以使用 `is_lock_free()` 成员函数，检查 `std::atomic<bool>` 上的操作是否无锁。这是除了 `std::atomic_flag` 之外，另一个所有原子类型都拥有的特征( `is_lock_free` )。

### 5.2.4 `std::atomic<T*>`

`std::atomic<T*>` 也有`load()`, `store()`, `exchange()`, `compare_exchange_weak()`和`compare_exchage_strong()` 成员函数，获取与返回的类型都是T*

除此之外，`std::atomic<T*>` 还为指针运算提供新的操作。基本操作有 `fetch_add()` 和 `fetch_sub()`，它们在存储地址上做原子加法和减法，并为+=, -=, ++和--提供简易的封装。对于内置类型的操作，例如：如果x是 `std::atomic<Foo*>` 类型的数组的首地址，然后 `x+=3` 让其偏移到第四个元素的地址，并返回一个普通的 `Foo*` 类型值，这个指针值是指向数组中第四个元素。`fetch_add()` 和 `fetch_sub()` 的返回值略有不同(所以 `x.ftech_add(3)` 让x指向第四个元素，并且函数返回指向第一个元素的地址)。这种操作也被称为“交换-相加”，并且这是一个原子的“读-改-写”操作，如同 `exchange()` 和 `compare_exchange_weak()` / `compare_exchange_strong()`一样。正像其他操作那样，返回值是一个普通的 `T*`值，而非是 `std::atomic<T*>` 对象的引用，所以调用代码可以基于之前的值进行操作：

  ```` cpp
  class Foo {};
  Foo some_array[5];
  std::atomic<Foo*> p(some_array);
  Foo* x = p.fetch_add(2);  // p加2，并返回原始值
  assert(x == some_array);
  assert(p.load() == &some_array[2]);
  x = (p += 1);  // p减1，并返回更新后的值
  assert(x == &some_array[3]);
  assert(p.load() == &some_array[3]);
  ````

函数也允许内存序作为给定函数的参数：
  
  ``` cpp
  p.fetch_add(3,std::memory_order_release);
  ```

因为fetch_add()和fetch_sub()都是“读-改-写”操作，可以使用任意的内存序，以及加入到一个释放序列中。因为没办法提供必要的信息(这些形式都具有memory_order_seq_cst语义)，所以指定的语序不支持操作符形式

### 5.2.5 标准原子整型的相关操作

如同普通的操作集合一样(`load()`, `store()`, `exchange()`, `compare_exchange_weak()`, 和 `compare_exchange_strong()`) ， `std::atomic<int>` 和 `std::atomic<unsigned long long>` 也是有一套完整的操作可以供使用：`fetch_add()`,  `fetch_sub()`, `fetch_and()`, `fetch_or()`, `fetch_xor()`，还有复合赋值方式((`+=`, `-=`, `&=`, `|=` 和`^=`)，以及`++`和`--`(`++x`, `x++`, `--x`和`x--`)。虽然对于普通的整型来说，这些复合赋值方式还不完全：除法、乘法和移位操作不在其中。因为，整型原子值通常用来作计数器，或者是掩码，所以以上操作的缺失显得不是那么重要。如果需要，可以使用`compare_exchange_weak()`完成

### 5.2.6 `std::atomic<>` 类模板

对于用户自定义类型，比较和复制是按位的（类似于 `std::memcmp` 和 `std::memcpy`）；不使用构造函数、赋值运算符或比较运算符。

For a union with bits that participate in the value representations of some members but not the others, compare-and-exchange might always fail because such padding bits have indeterminate values when they do not participate in the value representation of the active member.

Padding bits that never participate in an object's value representation are ignored.(since C++20)

注意，虽然使用 `std::atomic<float>` 或 `std::atomic<double>` (内置浮点类型满足使用`memcpy`和`memcmp`的标准)，但是在`compare_exchange_strong`函数中的表现可能会令人惊讶。当存储的值与当前值相等时，这个操作也可能失败，可能因为旧值是一个不同的表达(NaN)。这就不是对浮点数的原子计算操作了。

表5.3 总结每一个原子类型所能使用的操作

![原子类型所能使用的操作](..\src\img\总结原子类型所能使用的操作.png)

### 5.2.7 原子操作的非成员函数

不同的原子类型也有等价的非成员函数存在。大多数非成员函数的命名与对应成员函数有关，需要 `atomic_` 作为前缀(比如， `std::atomic_load()` )。这些函数都会重载不同的原子类型，指定内存序时会分成两种：一种没有标签，另一种以 `_explicit` 为后缀，并且需要额外的参数，或将内存序作为标签，亦或只有标签(例如， `std::atomic_store(&atomic_var,new_value)` 与 `std::atomic_store_explicit(&atomic_var,new_value,std::memory_order_release` )。不过，成员函数隐式引用原子对象，所有非成员函数都持有一个指向原子对象的指针(作为第一个参数)

例如：`std::atomic_load(&atomic_var)` 与 `atomic_var.load()` 等价, `std::atomic_is_lock_free(&atomic_var)` 与 `atomic_var.is_lock_free()` 等价, `std::atomic_store(&atomic_var,new_value)` 与 `atomic_var.store(new_value)` 等价，`a.load(std::memory_order_acquire)` 与 `std::atomic_load_explicit(&a, std::memory_order_acquire)` 等价。

非成员函数的设计是为了与C语言兼容，C语言中没有引用。

例如，`compare_exchange_weak()` 和 `compare_exchange_strong()` 成员函数的第一个参数(expected)是一个引用，而 `std::atomic_compare_exchange_weak()` (第一个参数是指向对象的指针)的第二个参数是一个指针。 `std::atomic_compare_exchange_weak_explicit()` 也需要指定成功和失败的内存序，而“比较/交换”成员函数都有一个单内存序(默认是 `std::memory_order_seq_cst` )，重载函数可以分别设置成功和失败的内存序。

对 `std::atomic_flag` 的操作是“反潮流”的，那些操作中它们“标志”的名称为： `std::atomic_flag_test_and_set()` 和 `std::atomic_flag_clear()` ，但是以 `_explicit` 为后缀的额外操作也能够指定内存顺序： `std::atomic_flag_test_and_set_explicit()` 和 `std::atomic_flag_clear_explicit()` 。

C++标准库也对 `std::shared_ptr<>` 智能指针类型提供非成员函数，这打破了“只有原子类型，才能提供原子操作”的原则。 `std::shared_ptr<>` 不是原子类型，但是C++标准委员会认为这很重要。可使用的原子操作有：`load`, `store`, `exchange`和`compare/exchange`，这些操作重载了标准原子类型的操作，并且可获取 `std::shared_ptr<>*` 作为第一个参数：

  ```` cpp
  std::shared_ptr<my_data> p;
  void process_global_data()
  {
    std::shared_ptr<my_data> local=std::atomic_load(&p);
    process_data(local);
  }
  void update_global_data()
  {
    std::shared_ptr<my_data> local(new my_data);
    std::atomic_store(&p,local);
  }
  ````

并行技术规范扩展提供了一种原子类型 `std::experimental::atomic_shared_ptr<T>` ，该类型声明在 `<experimental/atomic>` 头文件中。和 `std::atomic<UDT>` 一样，也有`load`，`store`，`exchange`，`compare/exchange` 这些操作。

这个类型支持无锁实现，所以可以作为独立类型提供，并不会给普通的 `std::shared_ptr` 实例增加开销。不过和 `std::atomic` 模板一样，可以使用成员函数`is_lock_free`，可以确定在对应的硬件平台上检查是否无锁。当实现不是无锁结构时，推荐使用 `std::experimental::atomic_shared_ptr` ，因为该类型会让代码更加清晰，确保所有的访问都是原子的，并且能避免由于忘记使用原子函数导致的数据竞争。

与原子类型和操作一样，如想用原子操作对应用进行加速，就需要对其性能进行分析，并且与其他同步机制进行对比

## 5.3 同步操作和强制排序

假设两个线程，一个向数据结构中填充数据，另一个读取数据结构中的数据。为了避免恶性条件竞争，第一个线程设置一个标志，用来表明数据已经准备就绪，从而第二个线程在这个标志设置前不能读取数据。

代码5.2 使用原子类型对读写操作进行强制排序

  ```` cpp
  std::vector<int> data; 
  std::atomic_bool data_ready(false);

  void reader_thread() {
    while (!data_ready.load()) {
      std::cout << "sleeping" << std::endl; 
      std::this_thread::sleep_for(std::chrono::milliseconds(1)); 
    }
    std::cout << data[0] << std::endl; 
  }

  void write_thread() {
    data.push_back(42); 
    data_ready = true; 
  }
  ````
  
访问顺序通过对 `std::atomic<bool>` 类型的 `data_ready` 变量进行操作完成，这些操作通过先行(happens-before)和同发(synchronizes-with)确定顺序。写入数据在写入 `data_ready` 前发生，读取 `data_ready` 发生在读取数据之前。当 `data_ready` 为true，写操作就会与读操作同步，建立一个“先行”的关系。因为“先行”关系是可传递的，所以写入数据先行于写入 `data_ready` ，这两个行为又先行于读取 `data_ready`，之前的操作都先行于读取数据，这样就强制了顺序：**写入数据先行于读取数据**。图5.2展示了“先行”关系在两线程间的重要性，读者线程的while循环中有一对迭代。

来看看“先行”和“同发”操作的真正意义

### 5.3.1 同步发生

如果线程A存储了一个值，并且线程B读取了这个值，线程A的存储操作与线程B的载入操作就是同步发生关系。

“同发”的基本想法：原子写操作W对变量x进行标记，同步对x进行的原子读操作，读取的是W操作写入的内
容，或是W之后，同一线程上的原子写操作对x写入的值，亦或是任意线程对x的一系列原子读-改-写操作(例
如，fetch_add()或compare_exchange_weak())

### 5.3.2 先行发生

如果操作A在线程上，并且线程先行于另一线程上的操作B，那么A就先行于B

“先行”关系是一个程序中基本构建块的操作顺序：指定了某个操作去影响另一个操作。

对于单线程来说：一个操作排在另一个之前，那这个操作就先执行。如果源码中操作A发生在操作B之前，那A就先行于B，这个称为排序先行。

如：代码5.2中对 data 的写入先于对 data_ready 的写入

如果操作间是无序执行，通常情况下就没有先行关系了

线程间的先行比较简单，并且依赖于同步关系：如果操作A在一个线程上，与另一个线程上的操作B同步，那么A就线程间先行于B。这也是一个传递关系：如果A线程间先行于B，并且B线程间先行于C，那么A就线程间先行于C。

线程间先行可以与排序先行相结合：如果操作A排序先行于操作B，并且操作B线程间先行于操作C，那么A线程间先行于C。同样的，如果A同步于B，并且B排序先于C，那么A线程间先行于C。当对数据进行一系列修改(单线程)时，只需要对数据进行一次同步即可。

**强先行发生关系**会有一些不同，不过在大多数情况下是一样的。如果操作A与操作B同步，或操作A的顺序在操作B之前，那么A就是强先行于B。也适用于顺序传递：如果A强先行于B，并且B强先行于C，那么A就肯定强先行于C。

事件在线程间的先行关系与普通事件有所区别，这里的区别就在于操作被标记为memory_order_consume(详见5.3.3节)，但不是强先行关系。由于大多数代码并不适用memory_order_consume内存序，因此这种区别在实际中可能不会表现的很明显。为了描述方便，本书中使用”先行发生“对这种关系进行描述。

为了理解这些差别，需要说一下原子操作使用的内存序，以及这些内存序和同步发生之间的联系。

### 5.3.3 原子操作的内存序

这里有六个内存序列选项可应用于对原子类型的操作：

1. memory_order_relaxed
2. memory_order_consume
3. memory_order_acquire
4. memory_order_release
5. memory_order_acq_rel
6. memory_order_seq_cst

除非为特定的操作指定一个序列选项，要不**内存序列默认都是memory_order_seq_cst**。

虽然有六个选项，但仅代表三种内存模型：**顺序一致性(sequentially consistent)**，**获取-释放序(memory_order_consume, memory_order_acquire, memory_order_release和memory_order_acq_rel)**和**自由序(memory_order_relaxed)**。

**顺序一致性**

默认序命名为顺序一致性，因为程序中的行为从任意角度去看，序列都保持一定顺序（全局排序一致性）。**如果原子实例的所有操作都是序列一致的，那么多线程就会如单线程那样以某种特殊的排序执行。**

代码5.4 全序——序列一致性

  ```` cpp
  #include <assert.h>
  #include <atomic>
  #include <thread>
  std::atomic<bool> x, y;
  std::atomic<int> z;
  void write_x() {
    x.store(true, std::memory_order_seq_cst);  // 1
  }
  void write_y() {
    y.store(true, std::memory_order_seq_cst);  // 2
  }
  void read_x_then_y() {
    while (!x.load(std::memory_order_seq_cst))
      ;
    if (y.load(std::memory_order_seq_cst))  // 3
      ++z;
  }
  void read_y_then_x() {
    while (!y.load(std::memory_order_seq_cst))
      ;
    if (x.load(std::memory_order_seq_cst))  // 4
      ++z;
  }
  int main() {
    x = false;
    y = false;
    z = 0;
    std::thread a(write_x);
    std::thread b(write_y);
    std::thread c(read_x_then_y);
    std::thread d(read_y_then_x);
    a.join();
    b.join();
    c.join();
    d.join();
    assert(z.load() != 0);  // 5: 不可能触发
  }
  ````

**非顺序一致性内存**

线程不保证一致性。

**自由序**

原子类型上的操作以自由序执行。同一线程中对于同一变量的操作还是遵从先行关系，但不同线程不需要规定顺序。唯一的要求是在访问同一线程中的单个原子变量不能重排序，当给定线程看到原子变量的值时，随后线程的读操作就不会去检索较早的那个值。当使用memory_order_relaxed时，不需要任何额外的同步，对于每个变量的修改顺序只存在于线程间共享。

代码5.5 非限制操作只有非常少的顺序要求

  ```` cpp
  #include <assert.h>
  #include <atomic>
  #include <thread>
  std::atomic<bool> x, y;
  std::atomic<int> z;
  void write_x_then_y() {
    x.store(true, std::memory_order_relaxed);  // 1
    y.store(true, std::memory_order_relaxed);  // 2
  }
  void read_y_then_x() {
    while (!y.load(std::memory_order_relaxed))
      ;                                     // 3
    if (x.load(std::memory_order_relaxed))  // 4
      ++z;
  }
  int main() {
    x = false;
    y = false;
    z = 0;
    std::thread a(write_x_then_y);
    std::thread b(read_y_then_x);
    a.join();
    b.join();
    assert(z.load() != 0);  // 5: 可能触发
  }
  ````

代码5.6 非限制操作——多线程版

  ```` cpp
  #include <atomic>
  #include <iostream>
  #include <thread>
  std::atomic<int> x(0), y(0), z(0);  // 1
  std::atomic<bool> go(false);        // 2
  unsigned const loop_count = 10;
  struct read_values {
    int x, y, z;
  };
  read_values values1[loop_count];
  read_values values2[loop_count];
  read_values values3[loop_count];
  read_values values4[loop_count];
  read_values values5[loop_count];
  void increment(std::atomic<int>* var_to_inc, read_values* values) {
    while (!go)
      std::this_thread::yield();  // 3 自旋，等待信号
    for (unsigned i = 0; i < loop_count; ++i) {
      values[i].x = x.load(std::memory_order_relaxed);
      values[i].y = y.load(std::memory_order_relaxed);
      values[i].z = z.load(std::memory_order_relaxed);
      var_to_inc->store(i + 1, std::memory_order_relaxed);  // 4
      std::this_thread::yield();
    }
  }
  void read_vals(read_values* values) {
    while (!go)
      std::this_thread::yield();  // 5 自旋，等待信号
    for (unsigned i = 0; i < loop_count; ++i) {
      values[i].x = x.load(std::memory_order_relaxed);
      values[i].y = y.load(std::memory_order_relaxed);
      values[i].z = z.load(std::memory_order_relaxed);
      std::this_thread::yield();
    }
  }

  void print(read_values* v) {
    for (unsigned i = 0; i < loop_count; ++i) {
      if (i)
        std::cout << ",";
      std::cout << "(" << v[i].x << "," << v[i].y << "," << v[i].z << ")";
    }
    std::cout << std::endl;
  }
  int main() {
    std::thread t1(increment, &x, values1);
    std::thread t2(increment, &y, values2);
    std::thread t3(increment, &z, values3);
    std::thread t4(read_vals, values4);
    std::thread t5(read_vals, values5);
    go = true;  // 6 开始执行主循环的信号
    t5.join();
    t4.join();
    t3.join();
    t2.join();
    t1.join();
    print(values1);  // 7 打印最终结果
    print(values2);
    print(values3);
    print(values4);
    print(values5);
  }
  ````

