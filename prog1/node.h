#ifndef NODE_
#define NODE_

template<class T>
class node {
  public:
    T data;
    node<T> * next;
    node<T> * prev;
    node<T> * up;
    node<T> * down;
    node() {next = nullptr; prev = nullptr; up = nullptr; down = nullptr;}
    node(T item) {
      data = item;
      next = nullptr;
      prev = nullptr;
      up = nullptr;
      down = nullptr;
    }
};

#endif