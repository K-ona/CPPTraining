# 设计无锁的并发数据结构

互斥量是一个强大的工具，可以保证在多线程情况下安全的访问数据结构，且不会有条件竞争或破坏不变量的情况存在。使用互斥量的原因很简单：就是让互斥量来保护数据。不过，这并不会如所想的那样，可以回看一下第3章，回顾一下死锁形成的原因，回顾一下基于锁的队列和查询表的例子，看一下细粒度锁是如何影响并发的。如果能写出一个无锁安全的并发数据结构，那就能避免这些问题。

本章中还会使用原子操作(第5章介绍)的内存序，来构建无锁数据结构。这样的数据结构不是那么容易正确实现的，所以要格外小心，并且让其问题会很难复现。我们将从无锁数据结构的定义开始，通过几个例子来了解使用无锁数据结构的意义，最后给出通用的指导意见。

## 7.1 定义和意义

使用互斥量、条件变量，以及future可以用来同步算法和数据结构。**调用库函数将会挂起执行线程**，直到其他线程完成某个特定动作。库函数将调用阻塞操作来对线程进行阻塞，在阻塞解除前线程无法继续自己的任务。通常，操作系统会完全挂起一个阻塞线程(并将其时间片交给其他线程)，直到解阻塞。“解阻塞”的方式很多，比如互斥锁解锁、通知条件变量达成，或让“future状态”就绪。

不使用阻塞库的数据结构和算法称为“无阻塞结构”。不过，无阻塞的数据结构并非都是无锁的，那么就来见识一下各种各样的无阻塞的数据结构吧！

### 7.1.1 非阻塞数据结构

代码7.1 使用 std::atomic_flag 实现了一个简单的自旋锁

  ```` cpp
  #include <atomic>

  class spinlock_mutex {
    std::atomic_flag flag;

  public:
    spinlock_mutex() : flag(ATOMIC_FLAG_INIT) {}
    void lock() {
      while (flag.test_and_set(std::memory_order_acquire))
        ;
    }
    void unlock() { flag.clear(std::memory_order_release); }
  };
  ````

非阻塞数据结构的类型定义：

- 无阻碍——如果其他线程都暂停了，任何给定的线程都将在一定时间内完成操作。
- 无锁——无锁是无阻碍的，如果多个线程对一个数据结构进行操作，经过一定时间后，其中一个线程将完成其操作。
- 无等待——无等待是无锁的，即使有其他线程也在对该数据结构进行操作，每个线程都将在一定的时间内完成操作。

大多数情况下无阻塞算法用的很少——其他线程都暂停的情况太少见了，因此这种方式用于描述一个失败的无锁实现更为合适。

### 7.1.2 无锁数据结构

无锁结构意味着线程可以并发的访问数据结构，线程不能做相同的操作。一个无锁队列可能允许一个线程压入数据，另一个线程弹出数据，当有两个线程同时添加元素时，将破坏这个数据结构。不仅如此，当调度器中途挂起其中一个访问线程时，其他线程必须能够继续完成自己的工作，**而无需等待挂起线程。**

具有“比较/交换”操作的数据结构，通常有一个循环。使用“比较/交换”操作的原因：当有其他线程同时对指定的数据进行修改时，代码将尝试恢复数据。当其他线程挂起时，“比较/交换”操作执行成功，这样的代码就是无锁的。

当执行失败时，需要一个自旋锁，那么结构就是“无阻塞-有锁”的结构。

无锁算法中的循环会让一些线程处于“饥饿”状态。如有线程在“错误”时间执行，那么会有线程将会不停的尝试所要完成的操作(其他程序继续执行)。“无锁-无等待”数据结构的出现，就为了避免这种问题。

### 7.1.3 无等待数据结构

无等待数据结构：首先是无锁数据结构，并且每个线程都能在有限的时间内完成操作，不管其他线程是如何工作的。

如果操作会和其他线程的行为有冲突，从而算法可能会进行若干次尝试，因此无法做到无等待。

本章的大多数例子都有一种特性——对compare_exchange_weak或compare_exchange_strong操作进行循环，并且循环次数没有上限。操作系统对线程进行进行管理，有些线程的循环次数非常多，有些线程的循环次数就非常少。因此，这些操作是无等待的。

正确实现一个无等待结构十分困难，要保证每个线程都能在有限的步骤内完成操作，必须确保每次执行的操作都是一次性的，并且当前线程中的操作不会影响其他线程的操作，这就会让所使用到的操作变的相当复杂。

先来找一下成本和收益的平衡点吧！

### 7.1.4 无锁数据结构的利与弊

使用无锁结构的主要原因：最大化并发。使用基于锁的容器，会让线程阻塞或等待，并且互斥锁削弱了结构的并发性。无锁数据结构中，某些线程可以逐步执行。无等待数据结构中，每一个线程都可以独自向前运行，这种理想的方式实现起来很难。如果结构太简单，反而不容易实现。

使用无锁数据结构的第二个原因就是鲁棒性。当一个线程在持有锁时被终止，那么数据结构将会永久性的破坏。不过，当线程在无锁数据结构上执行操作，在执行到一半终止时，数据结构上的数据没有丢失(除了线程本身的数据)，其他线程依旧可以正常执行。

另一方面，当不能限制访问数据结构的线程数量时，就需要注意不变量的状态，或选择替代品来保持不变量的状态。同时，还需要注意操作的顺序。为了避免未定义行为及相关的数据竞争，必须使用原子操作对修改操作进行限制。不过，**仅使用原子操作是不够的，需要确定其他线程看到的修改，是否遵循正确的顺序**。

因为，没有任何锁(有可能存在活锁)，死锁问题不会困扰无锁数据结构。**活锁的产生是两个线程同时尝试修改数据结构，但每个线程所做的修改操作都会让另一个线程重启，所以两个线程就会陷入循环，多次的尝试完成自己的操作。**。试想有两个人要过独木桥，当两个人从两头向中间走的时候，他们会在中间碰到，然后需要再走回出发的地方，再次尝试过独木桥。要打破僵局，除非有人先到独木桥的另一端(或是商量好了，或是走的快，或纯粹是运气)，要不这个循环将一直重复下去。不过活锁的存在时间并不久，因为其依赖于线程调度。所以只是对性能有所消耗，而不是一个长期问题，但这个问题仍需要关注。

==根据定义，因其操作执行步骤有上限，无等待的代码不会受活锁所困扰。换句话说，无等待的算法要比等待算法的复杂度高，即使没有其他线程访问数据结构，也可能需要更多步骤来完成相应操作。==

“无锁-无等待”代码的缺点：**虽然提高了并发访问的能力，减少了单个线程的等待时间，但是其可能会将整体性能拉低。** 首先，原子操作的无锁代码要慢于无原子操作的代码，原子操作就相当于无锁数据结构中的锁。不仅如此，**硬件必须通过同一个原子变量对线程间的数据进行同步**。

第8章将看到与“乒乓缓存”相关的原子变量(多个线程访问同时进行访问)，将会形成一个明显的性能瓶颈。

提交代码之前，无论是基于锁的数据结构，还是无锁的数据结构，对性能的检查都很重要(最坏的等待时间，平均等待时间，整体执行时间或者其他指标)。

## 7.2 无锁数据结构的例子

无锁结构依赖于原子操作和内存序，以确保多线程以正确的顺序访问数据结构

一些平台上无锁结构的实现(实际上在C++标准库中实现)使用了内部锁。另一些平台上，基于锁的简单数据结构可能会更加合适，还有很多平台的实现细节不明确。选择一种实现前，需要明确需求，并且配置各种选项以满足需求。

### 7.2.1 实现一个无锁的线程安全栈

代码7.2 不用锁实现push()

  ```` cpp
  #include <atomic>
  template <typename T>
  class lock_free_stack {
  private:
    struct node {
      T data;
      node* next;
      node(T const& data_)
          :  // 1
            data(data_) {}
    };
    std::atomic<node*> head;

  public:
    void push(T const& data) {
      const node* new_node = new node(data); // 2
      new_node->next = head.load(); // 3
      while (!head.compare_exchange_weak(new_node->next, new_node))
        ;
    }
  };
  ````

### 7.2.2 终止内存泄露：使用无锁数据结构管理内存

  ```` cpp
  #include <atomic>
  #include <memory>

  template <typename T>
  class lock_free_stack {
  private:
    std::atomic<unsigned> threads_in_pop; 
    std::atomic<node*> to_be_deleted; 
    struct node {
      std::shared_ptr<T> data;
      node* next;
      node(T const& data_)
          :  // 1
            data(std::make_shared<T>(data_)) {}
    };
    std::atomic<node*> head;

    static void delete_nodes(node* nodes) {
      while (nodes) {
        node* next = nodes->next; 
        delete nodes; 
        nodes = next; 
      }
    }

    void try_reclaim(node* old_head) {
      if (threads_in_pop == 1) {
        node* nodes_to_delete = to_be_deleted.exchange(nullptr); 
        if (!--threads_in_pop) {
          delete_nodes(nodes_to_delete); 
        } else if (nodes_to_delete) {
          chain_pending_nodes(nodes_to_delete); 
        }
        delete old_head; 
      } else {
        chain_pending_node(old_head); 
        --threads_in_pop; 
      }
    }

    void chain_pending_nodes(node* nodes) {
      node* last = nodes;
      while (const node* next = last->next) {
        last = next; 
      }
      chain_pending_nodes(nodes, last); 
    }

    void chain_pending_nodes(node* first, node* last) {
      last->next = to_be_deleted; 
      while (!to_be_deleted.compare_exchange_weak(last->next, first))
        ;
    }
    
    void chain_pending_node(node* n) {
      chain_pending_nodes(n, n); 
    }
    
  public:
    void push(T const& data) {
      const node* new_node = new node(data); // 2
      new_node->next = head.load(); // 3
      while (!head.compare_exchange_weak(new_node->next, new_node))
        ;
    }

    std::shared_ptr<T> pop() {
      ++threads_in_pop; 
      node* old_head = head.load(); 
      while (old_head &&
            !head.compare_exchange_weak(old_head, old_head->next))
        ;
      std::shared_ptr<T> res; 
      if (old_head) res.swap(old_head->data); 
      try_reclaim(old_head); 
      return res; 

      // return old_head ? old_head->data : std::make_shared<T>(); 
    }
  };
  ````

栈处于高负荷状态时，因为其他线程在初始化后都能使用`pop()`，所以 `to_be_deleted` 链表将会无限增加，会再次泄露。

不存在任何静态情况时，就得为回收节点寻找替代机制。关键是要确定无线程访问给定节点，这样给定节点就能回收，所以**最简单的替换机制就是使用风险指针**(hazard pointer)。

### 7.2.3 使用风险指针检测不可回收的节点

“风险指针”这个术语引用于Maged Michael的研究, 之所以这样叫是因为删除一个节点可能会让其他引用线程处于危险状态。其他线程持有已删除节点的指针对其进行解引用操作时，会出现未定义行为。

基本观点就是，当有线程去访问(其他线程)删除的对象时，会先对这个对象设置风险指针，而后通知其他线程——使用这个指针是危险的行为。当这个对象不再需要，就可以清除风险指针。

当线程想要删除一个对象，就必须检查系统中其他线程是否持有风险指针。当没有风险指针时，就可以安全删除对象。否则，就必须等待风险指针消失。这样，线程就需要周期性的检查要删除的对象是否能安全删除。

代码7.6 使用风险指针实现的pop()

  ```` cpp
  #include <atomic>
  #include <thread>
  #include <memory>
  #include <functional>

  unsigned const max_hazard_pointers = 100;
  struct hazard_pointer {
    std::atomic<std::thread::id> id; 
    std::atomic<void*> pointer; 
  };
  hazard_pointer hazard_pointers[max_hazard_pointers];

  class hp_owner {
    hazard_pointer* hp; 
  public:
    hp_owner(const hp_owner&) = delete;
    hp_owner& operator= (const hp_owner&) = delete; 
    hp_owner() : hp(nullptr) {
      for (unsigned i = 0; i < max_hazard_pointers; ++i) {
        std::thread::id old_id; 
        if (hazard_pointers[i].id.compare_exchange_strong(old_id, std::this_thread::get_id())) {
          hp = &hazard_pointers[i]; 
          break;
        }
      }
      if (!hp) {
        throw std::runtime_error("No hazard pointers available"); 
      }
    }

    std::atomic<void*>& get_pointer() {
      return hp->pointer; 
    }

    ~hp_owner() {
      hp->pointer.store(nullptr);
      hp->id.store(std::thread::id());
    }
  }; 

  std::atomic<void*>& get_hazard_pointer_for_current_thread() {
    thread_local static hp_owner hazard; 
    return hazard.get_pointer(); 
  }

  bool outstanding_hazard_pointers_for(void* p) {
    for (unsigned i = 0; i < max_hazard_pointers; ++i) {
      if (hazard_pointers[i].pointer.load() == p) {
        return true; 
      }
    }
    return false; 
  }

  template<typename T>
  void do_delete(void* p) {
    delete static_cast<T*>(p); 
  }

  struct data_to_reclaim {
    void* data; 
    std::function<void(void*)> deleter; 
    data_to_reclaim* next; 

    template<typename T>
    data_to_reclaim(T* p) : data(p), deleter(&do_delete<T>), next(nullptr) {} 

    ~data_to_reclaim() {
      deleter(data); 
    }
  };

  std::atomic<data_to_reclaim*> nodes_to_reclaim; 

  void add_to_reclaim_list(data_to_reclaim* node) {
    node->next = nodes_to_reclaim; 
    while (!nodes_to_reclaim.compare_exchange_weak(node->next, node)) 
      ;
  }

  template<typename T>
  void reclaim_later(T* data) {
    add_to_reclaim_list(new data_to_reclaim(data)); 
  }

  void delete_nodes_with_no_hazards() {
    data_to_reclaim* current = nodes_to_reclaim.exchange(nullptr);  // 关键，保证只有一个线程进行回收操作
    while (current) {
      data_to_reclaim* next = current->next; 
      if (outstanding_hazard_pointers_for(current->data)) {
        delete current; 
      } else {
        add_to_reclaim_list(current); 
      }
      current = next; 
    }
  }


  template <typename T>
  class lock_free_stack {
  private:
    struct node {
      std::shared_ptr<T> data;
      node* next;
      node(T const& data_)
          :  // 1
            data(std::make_shared<T>(data_)) {}
    };
    std::atomic<node*> head;


    std::shared_ptr<T> pop() {
      std::atomic<void*>& hp = get_hazard_pointer_for_current_thread();
      node* old_head = head.load();
      do {
        node* temp;
        do  // 1 直到将风险指针设为head指针
        {
          temp = old_head;
          hp.store(old_head);
          old_head = head.load();
        } while (old_head != temp);
      } while (old_head &&
              !head.compare_exchange_strong(old_head, old_head->next));
      hp.store(nullptr);  // 2 当声明完成，清除风险指针
      std::shared_ptr<T> res;
      if (old_head) {
        res.swap(old_head->data);
        if (outstanding_hazard_pointers_for(
                old_head))  // 3 在删除之前对风险指针引用的节点进行检查
        {
          reclaim_later(old_head);  // 4
        } else {
          delete old_head;  // 5
        }
        delete_nodes_with_no_hazards();  // 6
      }
      return res;
    }

  };

  ````

实现虽然很简单，也的确安全的回收了删除的节点，不过增加了很多开销。遍历风险指针数组需要检查`max_hazard_pointers`原子变量，并且每次`pop()`调用时，都需要再检查一遍。原子操作很耗时，所以`pop()`成为了性能瓶颈，不仅需要遍历节点的风险指针链表，还要遍历等待链表上的每一个节点。有`max_hazard_pointers`在链表中时，就需要检查`max_hazard_pointers`个已存储的风险指针。

**对风险指针(较好)的回收策略**

调用pop时，通过检查 hazard_pointers 数组进行判断是否删除对性能消耗极大，而且还不保证有节点会被删除
不过，当有 2 × max_hazard_pointers 个节点在等待列表中时，就能保证至少有 max_hazard_pointers 个节点可以回收。

这个方法的缺点(有增加内存使用的情况)：需要对回收链表上的节点进行原子计数，并且还有很多线程争相对回收的链表进行访问。

如果内存盈余，可以使用更多内存的来实现更好的回收策略：作为线程的本地变量，每个线程中的都拥有其自己的回收链表，这样就不需要原子计数了。这样的话，只需要分配 max_hazard_pointers x max_hazard_pointers 个节点。所有节点被回收完毕前时有线程退出，其本地链表可以像之前一样保存在全局中，并且添加到下一个线程的回收链表中，让下一个线程对这些节点进行回收。

### 7.2.4 使用引用计数

回到前面的问题：想要删除还能被其他读者线程访问的节点，该怎么办？
当能安全并准确的了解节点是否被引用，以及每一线程访问这些节点的具体时间，即可判断能否将对应节点删除。**风险指针是通过将使用中的节点放入到等待链表中，而引用计数顾名思义就是对每个节点上正在访问的线程进行计数**

代码7.9 无锁栈——使用无锁 std::shared_ptr<> 的实现

  ```` cpp
  #include <functional>
  #include <iostream>
  #include <atomic>
  #include <memory>
  #include <chrono>
  #include <thread>

  template<typename T>
  class lock_free_stack {
  private:
    struct node
    {
      std::shared_ptr<T> data; 
      std::shared_ptr<node> next; 
      node (const T& data_): data(std::make_shared<T>(data_)) {}
    };
    
    std::shared_ptr<node> head;
  public: 
    void push(const T& data) {
      const std::shared_ptr<node> new_node = std::make_shared<node>(data); 
      new_node->next = head;
      while (!std::atomic_compare_exchange_weak(&head, &new_node->next, new_node))
        ; 
    }

    std::shared_ptr<T> pop() {
      std::shared_ptr<node> old_head = std::atomic_load(&head); 
      while (old_head && !std::atomic_compare_exchange_weak(&head, &old_head, old_head->next))
        ;
      if (old_head) {
        std::atomic_store(&old_head->next, std::shared_ptr<node>()); 
        return old_head->data; 
      }
      return std::shared_ptr<T>(); 
    }
  };
  ````

对 `std::shared_ptr<>` 使用无锁原子操作的实现不仅很少见，而且能为其使用一致性的原子操作也很难(C++20 已弃用)。

多数情况下这与 `std::atomic<std::shared_ptr<T>>` 等价(除非是 `std::atomic<>` 不使用 `std::shared_ptr<T>` )，因为其具有特殊的复制语义，可以正确的处理引用计数。也就是 `std::experimental::atomic_shared_ptr<T>` 能在确保原子操作的同事，正确的处理引用计数。

代码7.10 使用 `std::experimental::atomic_shared_ptr<>` 实现的栈结构

  ```` cpp
  #include <functional>
  #include <iostream>
  #include <atomic>
  #include <memory>
  #include <chrono>
  #include <thread>

  template<typename T>
  class lock_free_stack {
  private: 
    struct node 
    {
      std::shared_ptr<T> data; 
      std::experimental::atomic_shared_ptr<node> next;
      node(T const& data_) : data(std::make_shared<T>(data_)) {}
    };
    std::experimental::atomic_shared_ptr<node> head;
  
  public:
    void push(T const& data) {
      std::shared_ptr<node> const new_node = std::make_shared<node>(data);
      new_node->next = head.load();
      while (!head.compare_exchange_weak(new_node->next, new_node))
        ;
    }

    std::shared_ptr<T> pop() {
      std::shared_ptr<node> old_head = head.load();
      while (old_head &&
            !head.compare_exchange_weak(old_head, old_head->next.load()))
        ;
      if (old_head) {
        old_head->next = std::shared_ptr<node>();
        return old_head->data;
      }
      return std::shared_ptr<T>();
    }

    ~lock_free_stack() {
      while (pop())
        ;
    }
  };
  ````

一些情况下，使用 `std::shared_ptr<>` 实现的结构并非无锁，需要手动管理引用计数。

一种方式是对每个节点使用两个引用计数：内部计数和外部计数。两个值的总和就是对这个节点的引用数。外部计数记录有多少指针指向节点，即在指针每次进行读取的时候，外部计数加1。当线程结束对节点的访问时，内部计数减1。

代码7.11 使用分离引用计数的方式实现无锁栈

```` cpp
template<typename T>
class lock_free_stack {
 private:
  struct counted_node_ptr; 
  struct node
  {
    std::shared_ptr<T> data; 
    std::atomic<int> internal_count; 
    counted_node_ptr next; 

    node(const T& data_) : data(std::make_shared<T>(data_)), internal_count(0) {}
  };

  struct counted_node_ptr
  {
    int external_count; 
    node* ptr; 
  };
  

  void increase_head_count(counted_node_ptr& old_counter) {
    counted_node_ptr new_counter; 
    do {
      new_counter = old_counter; 
      ++new_counter.external_count; 
    } while (!head.compare_exchange_strong(old_counter, new_counter)); 

    old_counter.external_count = new_counter.external_count; 
  }
  std::atomic<counted_node_ptr> head; 
  
 public:

  std::shared_ptr<T> pop() {
    counted_node_ptr old_head = head.load(); 
    for (;;) {
      increase_head_count(old_head); 
      node* ptr = old_head.ptr; 
      if (!ptr) {
        return std::shared_ptr<T>(); 
      }
      // compare_exchange_strong()成功时就拥有对应节点的所有权，并且可以和data进行交换后返回。
      if (head.compare_exchange_strong(old_head, ptr->next)) {
        std::shared_ptr<T> res; 
        res.swap(ptr->data); 

        // push 的时候加过1，表示可以访问，这里逻辑上删除之后应减1，于是这里要减2
        const int count_increase = old_head.external_count - 2; 
        if (ptr->internal_count.fetch_add(count_increase) == -count_increase) {
          delete ptr; 
        }
        return res; 
      } else if (ptr->internal_count.fetch_sub(1) == 1) {
        delete ptr; 
      }
    }
  }

  void push(const T& data) {
    counted_node_ptr new_node; 
    new_node.ptr = new node(data); 
    new_node.external_count = 1;
    new_node.ptr->next = head.load(); 
    while (!head.compare_exchange_weak(new_node.ptr->next, new_node)) 
      ;
  }

  ~lock_free_stack() {
    while (pop())
      ;
  }
};
````

`counted_node_ptr` 体积够小，能够让 `std::atomic<counted_node_ptr>` 无锁。一些平台上支持双字比较和交换操作，可以直接对结构体进行操作。平台不支持这样的操作时，最好使用`std::shared_ptr<>` 变量，当类型的体积过大，超出了平台支持指令，那么原子 `std::atomic<>` 将使用锁来保证其操作的原子性(从而会让“无锁”算法“基于锁”来完成)。

目前，使用默认 `std::memory_order_seq_cst` 内存序来规定原子操作的执行顺序。大多数系统中，这种操作方式很耗时，且同步操作的开销要高于其他内存序。现在，可以考虑对数据结构的逻辑进行修改，放宽内存序要求，没有必要在栈上增加过度的开销。现在让我们来检查一下栈的操作，并且思考，能对一些操作使用更加宽松的内存序么？如果使用了，能确保安全性么？

### 7.2.5 无锁栈上的内存模型

