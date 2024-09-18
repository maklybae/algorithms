#ifndef QUEUE_H
#define QUEUE_H

#include <stack>
#include <utility>

template <class T>
class Queue {
 public:
  void Push(T&& elem);
  T Pop();
  T& Front();
  T& Back();
  T Min();

 private:
  std::stack<std::pair<T, T>> push_stack_{};
  std::stack<std::pair<T, T>> pop_stack_{};
  std::pair<T, T>* push_stack_end_{};
  std::pair<T, T>* pop_stack_end_{};
};

#include "queue.tpp"

#endif