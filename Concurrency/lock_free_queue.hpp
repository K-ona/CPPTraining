#include <functional>
#include <iostream>
#include <atomic>
#include <memory>
#include <chrono>
#include <thread>

template <typename T>
class lock_free_queue {
 private:
  
  struct node; 
  struct counted_node_ptr
  {
    int external_count; 
    node* ptr; 
  };
  std::atomic<counted_node_ptr> head; 
  std::atomic<counted_node_ptr> tail;  

  // 让结构体的大小保持在一个机器字内，对其的操作就如同原子操作一样，还可以在多个平台上使用。
  struct node_counter {
    unsigned internal_count: 30; 
    unsigned external_counters: 2; 
  }; 

  struct node {
    std::atomic<T*> data;
    std::atomic<node_counter> count; 
    counted_node_ptr next; 

    node() {
      node_counter new_count; 
      new_count.internal_count = 0;
      new_count.external_counters = 2; 
      count.store(new_count); 
      next.ptr = nullptr; 
      next.external_count = 0;
    }

    void release_ref() {
      node_counter old_counter = count.load(std::memory_order_relaxed); 
      node_counter new_counter; 
      do {
        new_counter = old_counter; 
        --new_counter.internal_count; 
      } while (!count.compare_exchange_strong(old_counter, new_counter, 
               std::memory_order_acquire, std::memory_order_relaxed));  
      if (!new_counter.internal_count && !new_counter.external_counters)
        delete this; 
    }
  };

  node* pop_head() {
    node* const old_head = head.load();
    while (!head.compare_exchange_weak(old_head, old_head->next)) {
      if (old_head == tail.load())
        return nullptr;
    }
    return old_head;
  }

  static void increase_external_count(
    std::atomic<counted_node_ptr>& counter, 
    counted_node_ptr& old_counter) {
    counted_node_ptr new_counter; 
    do {
      new_counter = old_counter; 
      ++new_counter.external_count; 
    } while (!counter.compare_exchange_strong(
             old_counter, new_counter,
             std::memory_order_acquire, std::memory_order_relaxed)); 
    
    old_counter.external_count = new_counter.external_count; 
  }

  static void free_external_counter(counted_node_ptr& old_node_ptr) {
    node* const ptr = old_node_ptr.ptr; 
    int const count_increase = old_node_ptr.external_count - 2; 

    node_counter old_counter = ptr->count.load(std::memory_order_relaxed);
    node_counter new_counter; 
    do {
      new_counter = old_counter; 
      --new_counter.external_counters; 
      new_counter.internal_count += count_increase; 
    } while(!ptr->count.compare_exchange_strong(old_counter, 
                                                new_counter,
                                                std::memory_order_acquire, 
                                                std::memory_order_relaxed)); 
    if (!new_counter.internal_count &&
        !new_counter.external_counters) 
      delete ptr; 
  }

 public:
  lock_free_queue() : head(counted_node_ptr()), tail(head.load()) {}
  lock_free_queue(const lock_free_queue& other) = delete;
  lock_free_queue& operator=(const lock_free_queue& other) = delete;
  ~lock_free_queue() {
    while (true) {
      counted_node_ptr const old_head = head.load();
      if (!old_head.ptr) break;
      head.store(old_head.ptr->next);
      delete old_head.ptr;
    }
  }

  // version 1
  // void push(T new_value) {
  //   std::shared_ptr<T> new_data(std::make_shared<T>(new_value));
  //   node* p = new node;                  // 3
  //   node* const old_tail = tail.load();  // 4
  //   old_tail->data.swap(new_data);       // 5
  //   old_tail->next = p;                  // 6
  //   5，6 会发生data race
  //   tail.store(p);                       // 7
  // }

  // version 2
  // void push(T new_value) {
  //   std::unique_ptr<T> new_data(new T(new_data)); 
  //   counted_node_ptr new_next; 
  //   new_next.ptr = new node; 
  //   new_next.external_count = 1;
  //   for (;;) {
  //     const node* old_tail = tail.load(); 
  //     T* old_data = nullptr; 
  //     if (old_tail->data.compare_exchange_strong(old_data, new_data.get())) {
  //     old_tail 解引用时可能已经被delete了
  //       old_tail->next = new_next; 
  //       tail.store(new_next.ptr); 
  //       new_data.release(); 
  //       break;
  //     }
  //   }
  // }

  // version 3
  void push(T new_value) {
    std::unique_ptr<T> new_data(new T(new_value)); 
    counted_node_ptr new_next; 
    new_next.external_count = 1; 
    new_next.ptr = new node; 
    counted_node_ptr old_tail = tail.load(); 
    
    for (;;) {
      increase_external_count(tail, old_tail); 
      T* old_data = nullptr; 
      // 比较失败则忙等
      // 处理的技巧出自于“无锁技巧包”，等待线程可以帮助push()线程完成操作。
      if (old_tail.ptr->data.compare_exchange_strong(old_data, new_data.get())) {
        old_tail.ptr->next = new_next; 
        old_tail = tail.exchange(new_next); 
        free_external_counter(old_tail); 
        new_data.release(); 
        break; 
      }
      old_tail.ptr->release_ref(); 
    }
  }

  // std::shared_ptr<T> pop() {
  //   node* old_head = pop_head();
  //   if (!old_head) {
  //     return std::shared_ptr<T>();
  //   }
  //   std::shared_ptr<T> const res(old_head->data);  // 2
  //   delete old_head;
  //   return res;
  // }


  std::unique_ptr<T> pop() {
    counted_node_ptr old_head = head.load(std::memory_order_relaxed); 
    for (;;) {
      increase_external_count(head, old_head); 
      node* const ptr = old_head.ptr; 
      if (ptr == tail.load().ptr) {
        ptr->release_ref(); 
        return std::unique_ptr<T>(); 
      } 

      if (head.compare_exchange_strong(old_head, ptr->next)) {
        T* const res = ptr->data.exchange(nullptr); 
        free_external_counter(old_head); 
        return std::unique_ptr<T>(res); 
      }
      ptr->release_ref(); 
    }
  }
};

