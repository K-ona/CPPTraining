#include <unordered_map>
#include <vector>
#include <list>
#include <mutex>
#include <shared_mutex>
#include <memory>

template<typename T>
class threadsafe_list {
  struct node { // 1
    std::mutex m; 
    std::shared_ptr<T> data; 
    std::unique_ptr<node> next; 

    node() :  {} //2
    node(const T& value) : data(std::make_shared<T>(value)) {} // 3
  };

  node head; 
 
 public:
  threadsafe_list() {}
  ~threadsafe_list() {
    remove_if( [](const node&){
      return true; 
    } )
  }

  threadsafe_list(const threadsafe_list& other) = delete; 
  threadsafe_list& operator=(const threadsafe_list& other) = delete; 

  void push_front(const T& value) {
    std::unique_ptr<node> new_node(new node(value));  // 4
    std::lock_guard<std::mutex> lk(head.m); 
    new_node->next = std::move(head->next); // 5
    head->next = new_node;  //  6
  }

  template<typename Function>
  void for_each(Function f) { // 7
    node* current = &head; 
    std::unique_lock<std::mutex> lk(head.m); // 8
    while (node* next = current->next.get()) { // 9
      std::unique_lock<std::mutex> next_lk(next->m);  // 10
      lk.unlock();  // 11
      f(*next->data); // 12
      current = next; 
      lk = std::move(next_lk); // 13
    }
  }

  template<typename Predicate>
  std::shared_ptr<T> find_first_if(Predicate p) { // 14
    node* current = &head;
    std::unique_lock<std::mutex> lk(head.m); 
    while (node* next = current->next.get()) {
      std::unique_lock<std::mutex> next_lk(next->m); 
      lk.unlock(); 
      if (p(*next->data)) { // 15
        return next->data;  // 16
      }
      current = next; 
      lk = std::move(next_lk); 
    }
    return std::shared_ptr<T>(); 
  }


  template<typename Predicate>
  void remove_if(Predicate p) { // 17 
    node* current = &head; 
    std::unique_lock<std::mutex> lk(head.m); 
    while (const node* next = current->next.get()) {
      std::unique_lock<std::mutex> next_lk(next->m); 
      if (p(*next->data)) { // 18
        std::unique_ptr<node> tmp = std::move(current->next); 
        current->next = std::move(next->next); 
        next_lk.unlock(); 
      } else { // 20
        lk.unlock();  // 21
        current = next; 
        lk = std::move(next_lk); 
      }
    }
  }
}; 