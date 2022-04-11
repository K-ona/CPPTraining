// CRTP(Curiously Recurring Template Pattern)

#include <iostream>

// 1. 实现静态多态
template <class Derived>
struct Base {
  void Interface() {
    // ...
    static_cast<Derived*>(this)->Implementation();
    // ...
  }
};

struct Derived : Base<Derived> {
  void Implementation() { std::cout << "Implementation" << std::endl; }
};

// 2. 在基类中自定义派生类的行为
// 例：统计各派生类的个数
template <class Derived>
class ObjectCounter {
 private:
  inline static std::size_t count{0};

 protected:
  ObjectCounter() { ++count; }
  ObjectCounter(const ObjectCounter&) { ++count; }
  ObjectCounter(ObjectCounter&&) { ++count; }
  ~ObjectCounter() { --count; }

 public:
  static std::size_t CountLive() { return count; }
};

// 3. 实现侵入式双链表
template <typename T>
class LinkedList {
 public:
  // The "root" node is self-referential, and forms the basis of a circular
  // list (root_.Next() will point back to the start of the list,
  // and root_->Previous() wraps around to the end of the list).
  LinkedList() {}
  LinkedList(const LinkedList&) = delete;
  LinkedList& operator=(LinkedList&) = delete;
  void Append(LinkNode<T>* e) { e->InsertBefore(&root_); }
  LinkNode<T>* Head() const { return root_.Next(); }
  LinkNode<T>* Tail() const { return root_.Previous(); }
  const LinkNode<T>* End() const { return &root_; }
  bool Empty() const { return Head() == End(); }
 private:
  LinkNode<T> root_;
};

template <typename T>
class LinkNode {
 public:
  // LinkNode are self-referential as default.
  LinkNode() : previous_(this), next_(this) {}
  LinkNode(LinkNode<T>* previous, LinkNode<T>* next)
      : previous_(previous), next_(next) {}
  LinkNode(const LinkNode&) = delete;
  LinkNode& operator=(const LinkNode&) = delete;

  void InsertBefore(LinkNode<T>* e) {
    // ... 
  }
  void InsertBeforeAsList(LinkNode<T>* e) {
    // ...
  }
  void InsertAfter(LinkNode<T>* e) {
    // ...
  }
  void InsertAfterAsList(LinkNode<T>* e) {
    // ...
  }
  void RemoveFromList() {
    // ... 
  }

  LinkNode<T>* Previous() const { return previous_; }
  LinkNode<T>* Next() const { return next_; }

  const T* Value() const { return static_cast<const T*>(this); }
  T* Value() { return static_cast<T*>(this); }

 private:
  LinkNode<T>* previous_;
  LinkNode<T>* next_;
};

class MyNodeType : public LinkNode<MyNodeType> {
  // ...
}; 



template <typename T>
class MyVector : public ObjectCounter<MyVector<T>> {};

class MyCharString : public ObjectCounter<MyCharString> {};

int main() {
  MyVector<int> v1, v2;
  MyCharString s1;

  std::cout << "number of MyVector<int>: " << MyVector<int>::CountLive()
            << "\n";

  std::cout << "number of MyCharString: " << MyCharString::CountLive() << "\n";

  
  LinkedList<MyNodeType> list;
  LinkNode<MyNodeType>* n1 = ...;
  LinkNode<MyNodeType>* n2 = ...;
  LinkNode<MyNodeType>* n3 = ...;
  list.Append(n1);
  list.Append(n3);
  n2->InsertBefore(n3);
  for (LinkNode<MyNodeType>* node = list.Head();
    node != list.End();
    node = node->Next()) {
    MyNodeType* value = node->Value();
    ...
  }
  return 0;
}