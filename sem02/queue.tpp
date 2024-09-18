#ifndef QUEUE_TPP
#define QUEUE_TPP

#include <algorithm>
#include <stack>
#include <utility>

#include "queue.h"

template <class T>
void Queue<T>::Push(T&& elem) {
  T push_stack_min{push_stack_.empty() ? elem : std::min(push_stack_.top().second, elem)};
  push_stack_.emplace(std::forward<T>(elem), std::move(push_stack_min));

  if (push_stack_.size() == 1) {
    push_stack_end_ = &(push_stack_.top());
  }
}

template <class T>
T Queue<T>::Pop() {
  if (pop_stack_.empty()) {
    T pop_stack_min{push_stack_.top().first};
    pop_stack_.emplace(std::move(push_stack_.top().first), std::move(pop_stack_min));
    push_stack_.pop();
    pop_stack_end_ = &(pop_stack_.top());

    while (!push_stack_.empty()) {
      pop_stack_min = std::min(pop_stack_.top().second, push_stack_.top().first);
      pop_stack_.emplace(std::move(push_stack_.top().first), std::move(pop_stack_min));
      push_stack_.pop();
    }
    push_stack_end_ = nullptr;
  }
  T tmp{pop_stack_.top().first};
  pop_stack_.pop();
  if (pop_stack_.empty()) {
    pop_stack_end_ = nullptr;
  }
  return tmp;
}

template <class T>
T& Queue<T>::Front() {
  if (!pop_stack_.empty()) {
    return pop_stack_.top().first;
  }
  return push_stack_end_->first;
}

template <class T>
T& Queue<T>::Back() {
  if (!push_stack_.empty()) {
    return push_stack_.top().first;
  }
  return pop_stack_end_->first;
}

template <class T>
T Queue<T>::Min() {
  if (push_stack_.empty()) {
    return pop_stack_.top().second;
  }
  if (pop_stack_.empty()) {
    return push_stack_.top().second;
  }
  return std::min(push_stack_.top().second, pop_stack_.top().second);
}

#endif
