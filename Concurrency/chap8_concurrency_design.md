# 并发设计

第6、7章中了解如何使用这些工具来设计可并发访问的数据结构，使用并发代码要比使用/设计基本数据结构频繁的多。

认真思考如何进行并发化设计，对于每个编程项目来说都很重要。编写多线程代码时，需要考虑的因素比写串行代码多得多。不仅包括一般性因素，例如：封装、耦合和聚合(这些在很多软件设计书籍中有很详细的介绍)，还要考虑哪些数据需要共享，如何同步访问数据，哪些线程需要等待等等。

本章将会关注这些问题，从高层(但也是基本的)着眼，思考如何使用线程。哪些代码该在哪些线程上执行，以及对代码可读性的影响。并从底层实现细节上了解，如何构建共享数据来优化程序性能。

## 8.1 线程间划分工作

需要决定使用多少个线程，并且这些线程应该去做什么。需要决定是使用“全能”线程去完成所有的任务，还是使用“专业”线程去完成一件事情，或将两种方法混合。使用并发时，需要作出诸多选择来驱动并发，选择会决定代码的性能和可读性。因此选择至关重要，所以设计应用结构时，需要作出适当的决定。本节中，将看到很多划分任务的技术。

### 8.1.1 对数据进行预处理划分

并行化的 `std::for_each`

最简单的分配方式：第一组N个元素分配一个线程，下一组N个元素再分配一个线程，以此类推。不管数据怎么分，每个线程都会对分配给它的元素进行操作，但不会和其他线程进行沟通，直到处理完
成。

使用过MPI(Message Passing Interface) [1] 和OpenMP [2] 的同学对这个结构一定很熟悉：一项任务被分割成多个，放入一个并行任务集中，执行线程独立的执行这些任务，结果在主线程中合并。

### 8.1.2 递归划分

并行化的快速排序

快速排序有两个最基本的步骤：将数据划分到中枢元素之前或之后，然后对中枢元素之前和之后的两半数组再次进行快速排序。这里不能通过对数据的简单划分达到并行，因为只有在一次排序结束后，才能知道哪些项在中枢元素之前和之后。当要对这种算法进行并行化，很自然的会想到使用递归。每一级的递归都会多次调用quick_sort函数，因为需要知道哪些元素在中枢元素之前和之后。递归调用是完全独立的，因为其访问的是不同的数据集，并且每次迭代都能并发执行。图8.2展示了这样的递归划分。

代码8.1 使用栈的并行快速排序算法——等待数据块排序

  ```` cpp
  #include <chrono>
  #include <atomic>
  #include <vector>
  #include <thread>
  #include <boost/shared_ptr.hpp>
  #include <list>
  #include <future>

  using std::vector; 
  using std::list; 
  using std::promise; 

  template<typename T> 
  struct sorter
  {
    struct chunk_to_sort
    {
      std::list<T> data; 
      std::promise<std::list<T>> promise; 
    };

    thread_safe_stack<chunk_to_sort> chunks; 
    std::vector<std::thread> threads; 
    unsigned const max_thread_count; 
    std::atomic<bool> end_of_data; 

    sorter(): 
      max_thread_count(std::thread::hardware_concurrency() - 1), 
      end_of_data(false) {}

    ~sorter() {
      end_of_data = true; 
      for (auto &thread : threads) {
        thread.join();
      }
    }

    void try_sort_chunk() {
      boost::shared_ptr<chunk_to_sort> chunk = chunks.pop(); 
      if (chunk) {
        sort_chunk(chunk); 
      }
    }

    std::list<T> do_sort(std::list<T>& chunk_data) {
      if (chunk_data.empty()) {
        return chunk_data; 
      }
      std::list<T> result; 
      result.splice(result.begin(), chunk_data, chunk_data.begin()); 
      T const& partition_val = *chunk_data.begin(); 
      typename std::list<T>::iterator divide_point = std::partition(chunk_data.begin(), chunk_data.end(), [&](T const& val) {
        return val < partition_val; 
      });

      chunk_to_sort new_lower_chunk; 
      new_lower_chunk.data.splice(new_lower_chunk.data.end(), chunk_data, chunk_data.begin(), divide_point);
      
      std::future<std::list<T>> new_lower = new_lower_chunk.promise.get_futrure(); 
      chunks.push(std::move(new_lower_chunk)); 

      if (threads.size() < max_thread_count) {
        threads.push_back(std::thread(&sorter<T>::sort_thread, this);
      }
      
      std::list<T> new_higher(do_sort(chunk_data)); 
      result.splice(result.end(), new_higher); 

      while (new_lower.wait_for(std::chrono::seconds(0)) != std::future_status::ready) {
        try_sort_chunk(); 
      }

      result.splice(result.begin(), new_lower.get()); 
      return result; 
    }

    void sort_chunk(boost::shared_ptr<chunk_to_sort> const& chunk) {
      chunk->promise.set_value(do_sort(chunk->data)); 
    }

    void sort_thread() {
      while (!end_of_data) {
        try_sort_chunk(); 
        std::this_thread::yield(); 
      }
    }
  };


  template<typename T>
  std::list<T> parallel_quick_sort(std::list<T> input) {
    if (input.empty()) {
      return input; 
    }
    return sorter<T>().do_sort(input); 
  }
  ````

### 8.1.3 通过任务类型划分

任务几种划分方法：处理前划分和递归划分(都需要事先知道数据的长度固定)，还有上面的划分方式。事情并非总是这样好解决，当数据是动态生成或是通过外部输入，那这里的办法就不适用了。这种情况下，基于任务类型的划分方式，就要好于基于数据的划分方式。

另一种选择是让线程做专门的工作，就是每个线程做不同的工作，就像水管工和电工在建造一所屋子的时候，所做的不同工作那样。线程可能会对同一段数据进行操作，但对数据进行不同的操作。

对分工的排序，也就是分离关注点。每个线程都有不同的任务，这意味着真正意义上的线程独立。其他线程偶尔会向特定线程交付数据，或是通过触发事件的方式来进行处理。不过总体而言，每个线程只需要关注自己所要做的事情即可。其本身就是良好的设计，每一段代码只对自己的部分负责。

**分离关注**

多线程下有两个危险需要分离。第一个是对错误的担忧(主要表现为线程间共享着很多的数据)，第二是不同的线程要相互等待，这两种情况都是因为线程间很密切的交互。这种情况发生时，就需要看一下为什么需要这么多交互。**当所有交互都有同样的问题，就应该使用单线程来解决，并将引用同一源的线程提取出来。或者当有两个线程需要频繁的交流，在没有其他线程时，就可以将这两个线程合为一个线程。**

当通过任务类型对线程间的任务进行划分时，不应该让线程处于隔离态。当多个输入数据集需要使用同样的操作序列，**可以将序列中的操作分成多个阶段让线程执行**。

**划分任务序列**

当任务会应用到相同操作序列，去处理独立的数据项时，就可以使用 ==流水线(pipeline)== 系统进行并发。这好比一个物理管道：数据流从管道一端进入，进行一系列操作后，从管道另一端出去。

使用这种方式划分工作，可以为流水线中的每一阶段操作创建一个独立线程。当一个操作完成，数据元素会放在队列中，供下一阶段的线程使用。这就允许第一个线程在完成对于第一个数据块的操作时，第二个线程可以对第一个数据块执行管线中的第二个操作。

这种方式适合于操作开始前，且对输入数据长度不清楚的情况。例如：数据来源可能是从网络，或者可能是通过扫描文件系统来确定要处理的文件。

假设有20个数据项，需要在四核的机器上处理，并且每一个数据项需要四个步骤来完成操作，每一步都需要3秒来完成。如果将数据分给了四个线程，每个线程上就有5个数据项要处理。假设在处理时，没有其他线程对处理过程进行影响，在12秒后4个数据项处理完成，24秒后8个数据项处理完成，以此类推。当20个数据项都完成操作，就需要1分钟的时间。管线中就会完全不同，四步可以交给四个内核，第一个数据项可以被每一个核进行处理，所以其还是会消耗12秒。在12秒后你就能得到一个处理过的数据项，这相较于数据划分并没有好多少。不过，当流水线动起来，事情就会不一样了。第一个核处理第一个数据项后，数据项就会交给下一个内核，所以第一个核在处理完第一个数据项后，其还可以对第二个数据项进行处理。在12秒后，每3秒将会得到一个已处理的数据项，这就要好于每隔12秒完成4个数据项。

更平滑的操作能在某些情况下获益更多，考虑如下情况：当一个系统用来播放高清数字视频。为了让视频能够播放，至少要保证25帧每秒的解码速度。这些图像需要有均匀的间隔，才会给观众留有连续播放的感觉。一个应用可以在1秒解码100帧，不过在解完就需要暂停1s的时候，这个应用就没有意义了。另一方面，观众能接受在视频开始播放的时候有一定的延迟。这种情况，并行使用流水线就能得到稳定的解码率。

## 8.2 并发代码的性能

多处理系统中使用并发来提高代码的效率时，需要了解影响并发的效率的因素。即使使用多线程对关注点进行分离，还需要确定是否会对性能造成负面影响。

### 8.2.1 处理器数量

处理器数量是影响多线程应用的首要因素。

一个最多能开启16个并发线程的处理器，线程数量少于16个时，会有处理器处于空闲状态(除非系统同时需要运行其他应用，不过我们暂时忽略这种可能性)。另一方面，当多于16个线程在运行时(都没有阻塞或等待)，应用将会浪费处理器的运算时间在线程间进行切换，称其为==超额申请(oversubscription)==。

为了扩展线程的数量，且与硬件所支持的并发线程数一致，C++标准线程库提供 `std::thread::hardware_concurrency()` ，使用这个函数就能知道在给定硬件上可以扩展的线程数量了。

使用 `std::thread::hardware_concurrency()` 需要谨慎，因为不会考虑其他应用已使用的线程数量(除非已经将系统信息进行共享)。 `std::async()` 可以避免这个问题，标准库会对所有调用进行安排。同样，谨慎的使用线程池也可以避免这个问题。

理想算法可能会取决于问题规模与处理单元的比值。随着处理器数量的增加，另一个问题就会来影响性能：多个处理器尝试访问同一个数据。

### 8.2.2 数据争用与乒乓缓存

当两个线程在不同处理器上时，对同一数据进行读取，通常不会出现问题。因为数据会拷贝到每个线程的缓存中，并让两个处理器同时进行处理。当有线程对数据进行修改，并且需要更新到其他核芯的缓存中去，就要耗费一定的时间。这样的修改可能会让第二个处理器停下来，等待硬件内存更新缓存中的数据。

根据CPU指令，这是一个特别特别慢的操作。

思考下面的代码段：
  
  ```` cpp
  std::atomic<unsigned long> counter(0);
  void processing_loop()
  {
    while(counter.fetch_add(1,std::memory_order_relaxed)<100000000)
    {
      do_something();
    }
  }
  ````

如果另一个线程在另一个处理器上执行同样的代码，counter的数据需要在两个处理器之间进行传递，这两个处理器的缓存中间就存有counter的最新值(当counter的值增加时)。如果do_something()足够短，或有很多处理器来对这段代码进行处理时，处理器会互相等待。一个处理器准备更新这个值，另一个处理器在修改这个值，所以该处理器就需要等待第二个处理器更新完成，并且完成更新传递时才能执行更新，这种情况被称为高竞争(high contention)。如果处理器很少需要互相等待就是低竞争(low contention)。

循环中counter的数据将在每个缓存中传递若干次，这就是==乒乓缓存(cache ping-pong)==，这会对应用的性能有着重大的影响。当处理器因为等待缓存转移而停止运行时，这个处理器就不能做任何事情，所以对于整个应用来说这是一个坏消息。

考虑互斥锁

  ```` cpp
  std::mutex m;
  my_data data;
  void processing_loop_with_mutex()
  {
    while(true)
    {
      std::lock_guard<std::mutex> lk(m);
      if(done_processing(data)) break;
    }
  }
  ````

乒乓缓存可能会抵消互斥所带来的性能收益，因为所有线程(即使是读者线程)都会对互斥量进行修改。

随着处理器对数据访问次数的增加，对于互斥量的竞争就会增加，并且持有互斥量的缓存行会在核芯中进行转移，因此会增加不良的锁获取和释放次数。有些方法可以改善这个问题，就是让互斥量对多行缓存进行保护，不过这样的互斥量需要自己去实现。

如何避免乒乓缓存呢？答案就是：减少两个线程对同一个内存位置的竞争。

然而要实现起来并不简单。即使给定内存位置，因为**伪共享(false sharing)**可能还是会有乒乓缓存。

### 8.2.4 邻近数据(data proximity)

伪共享发生的原因：某个线程所要访问的数据过于接近另一线程的数据，另一个是与数据布局相关的陷阱会直接影响单线程的性能。

问题在于数据过于接近：单线程访问数据时，数据就已在内存中展开，分布在不同的缓存行上。另一方面，当内存中有紧凑数据时，数据就分布在同一缓存行上。因此，当数据分散时，将会有更多的缓存行从处理器的缓存上加载数据，这会增加访问内存的延迟，以及降低数据的性能(与紧凑的数据存储地址相比较)。

同样的，如果数据较分散，给定缓存行上就包含与当前线程有关和无关的数据。极端情况下，这就会浪费宝贵的缓存空间，增加处理器缓存缺失的情况，因为其他数据已经占有缓存中的位置，所以需要再从主存中添加对应数据项到缓存中。

现在，对于单线程代码来说任务切换(task switching)就很关键了。如果系统中的线程数量要比核芯多，每个核上都要运行多个线程。这就会增加缓存的压力，为了避免伪共享，==努力让不同线程访问不同缓存行==。当处理器切换线程时，要对不同内存行上的数据进行加载(当不同线程使用的数据跨越了多个缓存行时)，而非对缓存中的数据保持原样(当线程中的数据都在同一缓存行时)。C++17在头文件 `<new>` 中指定了一个常数 `std::hardware_constructive_interference_size` ，这是同一高速缓存行上的连续字节的最大数目(需要对齐)。将所需的数据大小控制在这个字节数内，就能提高缓存命中率。

如果线程数量多于内核或处理器数量，操作系统可能会选择将线程安排给这个核芯一段时间，之后再安排给另一个核芯一段时间。就需要将缓存行从一个内核上，转移到另一个内核上，也意味着要耗费很多时间。虽然，操作系统通常会避免这样的情况发生，不过当其发生的时候，对性能会有很大影响。当有超级多的线程准备运行时(非等待状态)，任务切换就会频繁发生。这个问题我们之前也接触过：超额申请。

### 8.2.5 超额申请和频繁的任务切换

多线程系统中，通常线程的数量要多于处理器的数量，除非在**大规模并行(massively parallel)**硬件上运行。

不过，线程会花费时间来等待外部I/O完成，或被互斥量阻塞，或等待条件变量等等，所以等待不是问题。使用
额外的线程来完成有用的工作，而非让线程在处理器处以闲置状态时持续等待

不过，这也并非长久之计，如果有很多额外线程，就会有很多线程准备执行。不过，当线程数远远大于可用处理器数量时，操作系统就会忙于切换任务，以确保每个任务都有时间运行，这将增加切换任务的时间开销，**和缓存问题造成同一结果。**

当无限制的产生新线程，超额申请就会加剧，或者在通过任务类型对任务进行划分的时候，线程数量大于处理器数量。这时，对性能影响的因素是CPU的能力，而非I/O。

## 8.3 为多线程性能设计数据结构

### 8.3.1 划分数组元素

即有很大的数据块需要在线程间进行划分，仔细观察所有数据访问的各个方面，以及确定性能问题产生的原因。

各种领域中，出现问题的情况都很相似：**改变划分方式就能够提高性能**，不需要对基本算法进行任何修改。

例：大矩阵乘法

划分方法：

1. 按结果矩阵的行划分
2. 按结果矩阵的列划分
3. 按结果矩阵的行数划分

划分后的性能：3 > 2 > 1

### 8.3.2 其他数据结构中的访问模式

同样的考虑适用于数据结构的数据访问模式，如同优化对数组的访问：

- 尝试调整数据在线程间的分布，让同一线程中的数据紧密联系（物理上）在一起
- 尝试减少线程上所需的数据量
- 尝试让不同线程访问不同的存储位置，以避免伪共享

比起数组，应用于其他数据结构上会比较麻烦。例如：对二叉树划分就要比其他结构困难，有用与没用要取决于树的平衡性，以及需要划分的节点数量。

假设一个类，其中包含数据项和一个用于保护数据的互斥量，对于需要获取互斥量从而进行数据访问的线程来说，互斥量和数据在内存中很接近是理想的情况：在载入互斥量时，可能已经同时也加载了（加载到缓存中）所需的数据。

不过也带来一个缺点：当其他线程尝试锁住互斥量时(第一个线程还没有释放)，线程就能对数据项进行访问（互斥锁是作为“读-改-写”原子操作实现的，对于相同位置的操作都需要先获取互斥量，如果互斥量已锁，就会调用系统内核。在 “读” 的时候可能会让数据存储到缓存中），从而会影响到已持有互斥量的线程的性能。

## 8.4 设计并发代码的注意事项

除了性能、数据访问模式，还需要考虑**异常安全**和**可拓展性**。

随着核数的增加，性能越来越高(无论是在减少执行时间，还是增加吞吐率)，这样的代码称为“可扩展”代码。理想状态下，性能随着核数的增加线性增长，也就是当系统有100个处理器时，其性能是系统只有1核时的100倍。

异常安全是一个正确性问题，如果代码不是异常安全的，最终会破坏不变量，或是造成条件竞争，亦或是操作抛出异常意外终止应用。我们就先来看一下异常安全的问题。

### 8.4.1 并行算法中的异常安全

异常安全是衡量C++代码很重要的指标，并发代码也不例外。实际上，相较于串行算法，并行算法常会更注意异常问题。操作在串行算法中抛出异常时，算法只需要对其本身进行处理，就可以避免资源泄露和损坏不变量，这里允许异常传递给调用者，由调用者对异常进行处理。在并行算法中很多操作要运行在独立的线程上，所以就不能传播异常。如果函数在创建新线程后异常退出，那么应用会终止。

让我们回顾一下代码2.8中的`parallel_accumulate`函数：

代码8.2 `std::accumulate` 的原始并行版本(源于代码2.8)

  ```` cpp
  #include <thread>

  template <typename Iterator, typename T>
  struct accumulate_block {
    void operator()(Iterator first, Iterator last, T& result) {
      result = std::accumulate(first, last, result);  // 1
    }
  };

  template <typename Iterator, typename T>
  T parallel_accumulate(Iterator first, Iterator last, T init) {
    unsigned long const length = std::distance(first, last);  // 2
    if (!length)
      return init;

    unsigned long const min_per_thread = 25;
    unsigned long const max_threads =
        (length + min_per_thread - 1) / min_per_thread;

    unsigned long const hardware_threads = std::thread::hardware_concurrency();
    unsigned long const num_threads =
        std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

    unsigned long const block_size = length / num_threads;

    std::vector<T> results(num_threads);                // 3
    std::vector<std::thread> threads(num_threads - 1);  // 4
    Iterator block_start = first;                       // 5

    for (unsigned long i = 0; i < (num_threads - 1); ++i) {
      Iterator block_end = block_start;  // 6
      std::advance(block_end, block_size);
      threads[i] = std::thread(  // 7
          accumulate_block<Iterator, T>(), block_start, block_end,
          std::ref(results[i]));
      block_start = block_end;  // 8
    }

    accumulate_block()(block_start, last, results[num_threads - 1]);  // 9
    
    std::for_each(threads.begin(), threads.end(),
                  std::mem_fn(&std::thread::join));
    return std::accumulate(results.begin(), results.end(), init);  // 10
  }
  ````

异常在哪抛出：在调用函数的地方或在用户定义类型上执行某个操作时抛出异常。

如果仔细了解过新线程用来完成什么样的工作，要返回一个计算的结果的同时，允许代码产生异常，可以将 `std::packaged_task` 和 `std::future` 结合使用。如果使用 `std::packaged_task` 重新构造代码，可能是如下模样。

代码8.3 使用 `std::packaged_task` 的并行 `std::accumulate`

  ```` cpp
  template <typename Iterator, typename T>
  T parallel_accumulate(Iterator first, Iterator last, T init) {
    unsigned long const length = std::distance(first, last);
    if (!length)
      return init;
    unsigned long const min_per_thread = 25;
    unsigned long const max_threads =
        (length + min_per_thread - 1) / min_per_thread;
    unsigned long const hardware_threads = std::thread::hardware_concurrency();
    unsigned long const num_threads =
        std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
    unsigned long const block_size = length / num_threads;
    std::vector<std::future<T> > futures(num_threads - 1);
    std::vector<std::thread> threads(num_threads - 1);
    join_threads joiner(threads);  // 1
    Iterator block_start = first;
    
    for (unsigned long i = 0; i < (num_threads - 1); ++i) {
      Iterator block_end = block_start;
      std::advance(block_end, block_size);
      std::packaged_task<T(Iterator, Iterator)> task(
          accumulate_block<Iterator, T>());
      futures[i] = task.get_future();
      threads[i] = std::thread(std::move(task), block_start, block_end);
      block_start = block_end;
    }

    T last_result = accumulate_block()(block_start, last);
    T result = init;

    for (unsigned long i = 0; i < (num_threads - 1); ++i) {
      result += futures[i].get();  // 2
    }
    result += last_result;
    return result;
  }
  ````

**`std::async()`的异常安全**

代码8.5 异常安全并行版 `std::accumulate` ——使用 `std::async()`

```` cpp
template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
  unsigned long const length = std::distance(first, last);  // 1
  unsigned long const max_chunk_size = 25;
  if (length <= max_chunk_size) {
    return std::accumulate(first, last, init);  // 2
  } else {
    Iterator mid_point = first;
    std::advance(mid_point, length / 2);  // 3
    std::future<T> first_half_result =
        std::async(parallel_accumulate<Iterator, T>,  // 4
                   first, mid_point, init);
    T second_half_result = parallel_accumulate(mid_point, last, T());  // 5
    return first_half_result.get() + second_half_result;               // 6
  }
}
````

这个版本要比之前简单很多，并且这个版本也是异常安全的。和之前一样，要确定序列的长度①，如果其长度小于数据块包含数据的最大值，可以直接调用 `std::accumulate` ②。如果元素的数量超出了数据块包含数据的最大值，就需要找到数量中点③，将这个数据块分成两部分，然后再生成一个异步任务对另一半数据进行处理④。第二半的数据是通过直接的递归调用来处理的⑤，之后将两个块的结果加和到一起⑥。标准库能保证 `std::async` 的调用能够充分的利用硬件线程，并且不会产生线程的超额申请，一些“异步”调用在get()⑥后同步执行。

优雅的地方不仅在于利用硬件并发的优势，还能保证异常安全。如果有异常在递归⑤中抛出，通过 `std::async` ④所产生的future，将异常在传播时销毁。这就需要依次等待异步任务的完成，因此也能避免悬空线程的出现。另外，当异步任务抛出异常，且被future所捕获后，在对get()⑥调用的时候，future中存储的异常会再次抛出。

### 8.4.2 可扩展性和Amdahl定律

扩展性代表了应用利用系统中处理器执行任务的能力。

一种极端的方式就是将应用写死为单线程运行，这种应用就是完全不可扩展的。即使添加了100个处理器到你的系统中，应用的性能都不会有任何改变。

另一种就是像SETI@Home[3]项目一样，让应用使用系统中成千上万的处理器(以个人电脑的形式加入网络的用户)成为可能。

对于任意的多线程程序，运行时的工作线程数量会有所不同。应用初始阶段只有一个线程，之后会在这个线程上衍生出新的线程。理想状态：每个线程都做着有用的工作，不过这种情况几乎是不可能发生的。线程通常会花时间进行互相等待，或等待I/O操作的完成。

一种简化的方式就是就是将程序划分成“串行”和“并行”部分。串行部分：只能由单线程执行一些工作的地方。并行部分：可以让所有可用的处理器一起工作的部分。当在多处理系统上运行应用时，“并行”部分理论上会完成的相当快，因为其工作被划分为多份，放在不同的处理器上执行。“串行”部分则不同，只能一个处理器执行所有工作。这样的(简化)假设下，就可以随着处理数量的增加，估计一下性能的增益：当程序“串行”部分的时间用fs来表示，那么性能增益(P)就可以通过处理器数量(N)进行估计：

$$
  P = \frac{1}{f_s + \frac{1 - f_s}{N}}
$$

这就是Amdahl定律，讨论并发程序性能的时候都会引用到的公式。如果每行代码都能并行化，串行部分就为0，性能增益就为N。或者，当串行部分为1/3时，当处理器数量无限增长，都无法获得超过3的性能增益。

Amdahl定律明确了，对代码最大化并发可以保证所有处理器都能用来做有用的工作。如果将“串行”部分的减小，或者减少线程的等待，就可以在多处理器的系统中获取更多的性能收益。或者，当能提供更多的数据让系统进行处理，并且让并行部分做最重要的工作，就可以减少“串行”部分，以获取更高的性能增益。

扩展性：当有更多的处理器加入时，减少单个动作的执行时间，或在给定时间内做更多工作。有时这两个指标是等价的(如果处理器的速度相当快，就可以处理更多的数据)。选择线程间的工作划分的技术前，需要辨别哪些方面是能够扩展的。

本节开始已经提到，线程并非任何时候都做的是有用的工作。有时也会等待其他线程，或者等待I/O完成，亦或是等待其他事情。如果线程等待时，系统中还有必要的任务需要完成，就可以将等待“隐藏”起来。

### 8.4.3 使用多线程隐藏延迟

之前讨论了很多有关多线程性能的话题。现在假设，线程在一个处理器上运行时不会偷懒，并且做的工作都很有用。然而实际应用中，线程会经常因为等待某些事情而阻塞。

不论等待的理由是什么，线程阻塞就意味着在等待CPU时间片。处理器将会在阻塞的时间内运行另一个线程，而不是什么事情都不做。因此，当知道一些线程需要耗费相当一段时间进行等待时，可以利用CPU的空闲时间去运行一个或多个线程。

试想一个病毒扫描程序，使用流水线对线程间的工作进行划分。第一个线程对文件系统进行检查，并将它们放入一个队列中。同时，另一个线程从队列中获取文件名，加载文件，之后进行病毒扫描。线程对文件系统中的文件进行扫描就会受到I/O操作的限制，所以可以通过执行额外的扫描线程，充分利用CPU的“空闲”时间。这时还需要一个文件搜索线程，以及足够多的扫描线程。当扫描线程为了扫描文件，还要从磁盘上读取到重要部分的文件时，就能体会到多扫描线程的意义所在了。不过，某些时候线程会过多，系统将会因为越来越多的任务切换而降低效率，就像8.2.5节描述的那样。

同之前一样，这也是一种优化，对修改(线程数量)前后性能的测量很重要。

应用可能不用额外的线程，而使用CPU的空闲时间。

例如，如果线程因为I/O操作阻塞，这个线程可能会使用异步I/O(如果可以用的话)，当I/O操作在后台执行完成后，线程就可以做工作了。其他情况下，一个线程等待其他线程去执行一个操作时，比起阻塞，不如让阻塞线程自己来完成这个操作，就像在第7章中看到的无锁队列那样。

一个极端的例子中，当一个线程等待任务完成，并且这个任务还没有被其他任何线程所执行时，等待线程就可以执行这个任务，或执行另一个不完整的任务。代码8.1中排序函数会持续的对数据进行排序，即使那些数据已经不需要排序了。

比起添加线程数量对处理器进行充分利用外，有时也要在增加线程**确保外部事件能够及时的响应**，以提升系统的响应能力。

### 8.4.4 使用并发提高响应能力

很多流行的图形化用户接口框架都是事件驱动型(event driven)，对图形化接口进行操作是通过按下按键或移动鼠标进行。为了确定所有事件和信息都能被正确的处理，应用通常会有一个事件循环，就像下面的代码：

  ```` cpp
  while(true)
  {
    event_data event=get_event();
    if(event.type==quit)
      break;
    process(event);
  }
  ````

API中的细节可能不同，不过结构通常是一样的：等待一个事件，对其做必要的处理，之后等待下一个事件。如果是单线程应用，就会让长期任务很难执行完成。为了确保用户输入能得到及时的处理，无论应时在做些什么，`get_event()` 和 `process()` 必须以合理的频率调用。这就意味着任务需要周期性的悬挂，并且返到事件循环中，`get_event()/process()` 必须在合适的地方进行调用，且每个选项的复杂程度取决于任务的实现方式。

通过**使用并发分离关注点**，可以将一个很长的任务交给一个全新的线程，并且留下一个专用的GUI线程来处理这些事件。线程可以通过简单的机制进行通讯，**而不是将事件处理代码和任务代码混在一起**。

代码8.6 将GUI线程和任务线程进行分离

```` cpp
std::thread task_thread;
std::atomic<bool> task_cancelled(false);
void gui_thread() {
  while (true) {
    event_data event = get_event();
    if (event.type == quit)
      break;
    process(event);
  }
}

void task() {
  while (!task_complete() && !task_cancelled) {
    do_next_operation();
  }
  if (task_cancelled) {
    perform_cleanup();
  } else {
    post_gui_event(task_complete);
  }
}

void process(event_data const& event) {
  switch (event.type) {
    case start_task:
      task_cancelled = false;
      // 启动任务线程后 回到gui线程
      task_thread = std::thread(task);
      break;
    case stop_task:
      task_cancelled = true;
      task_thread.join();
      break;
    case task_complete:
      task_thread.join();
      display_results();
      break;
    default:
      //...
  }
}
````

## 8.5 实践并发代码

为特殊的任务设计并发代码时，需要根据任务来考虑之前提到的问题。为了展示以上的注意事项如何应用，看一下在C++标准库中三个标准函数的并行实现。

### 8.5.1 并行版 `std::for_each`

`std::for_each` 的原理很简单：其对某个范围中的元素，依次使用用户提供的函数。并行和串行的最大区别就是函数的调用顺序。 `std::for_each` 是对范围中的第一个元素调用用户函数，接着是第二个，以此类推。在并行实现中对于每个元素的处理顺序就不能保证了。

为了实现这个函数的并行版本，需要对每个线程所处理的元素进行划分。事先知道元素数量，所以可以在处理前对数据进行划分(详见8.1.1节)。假设只有并行任务运行，就可以使用 `std::thread::hardware_concurrency()` 来决定线程的数量。同样，这些元素都能独立的处理，可以使用连续的数据块来避免伪共享(详见8.2.3节)。

这里的算法类似于并行版的 `std::accumulate` (详见8.4.1节)，不过比起计算每一个元素的加和，这里对每个元素仅仅使用了指定功能的函数。因为不需要返回结果，要将异常传递给调用者，就需要使用 `std::packaged_task` 和 `std::future` 对线程中的异常进行转移。

### 8.5.2 并行版 `std::find`

`find` 与 `for_each` 不一样，当第一个元素满足条件时，就没必要对剩余元素进行搜索了
需要考虑如何通知其他线程停止搜索，因此，需要设计代码对其进行使用——当得到想要的答案时，就中断其他任务的执行。

### 8.5.3 并行版 `std::partial_sum`

`std::partial_sum` 会计算给定范围中的每个元素，并用计算后的结果将原始序列中的值替换掉。比如，有一个序列[1，2，3，4，5]，执行该算法后会成为：[1，3(1+2)，6(1+2+3)，10(1+2+3+4)，15(1+2+3+4+5)]。让这样一个算法并行起来会很有趣，因为这里不能讲任务分块，对每一块进行独立的计算

