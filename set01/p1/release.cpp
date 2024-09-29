#include <algorithm>
#include <stdexcept>
#include <unordered_set>

#include "list.h"

List::List() : head{nullptr}, tail{nullptr}, _size{0} {
}

List::List(const List& other) : head{nullptr}, tail{nullptr}, _size{0} {
  merge(other);
}

List::List(std::vector<int> array) : head{nullptr}, tail{nullptr}, _size{0} {
  for (auto num : array) {
    push_back(num);
  }
}

List::~List() {
  while (!empty()) {
    pop_front();
  }
}

int List::front() {
  return head->value;
}

int List::back() {
  return tail->value;
}

void List::push_back(int value) {
  auto node = new Node{tail, nullptr, value};

  // List is empty
  if (tail) {
    tail->next = node;
  } else {
    head = node;
  }

  tail = node;
  ++_size;
}

void List::push_front(int value) {
  auto node = new Node{nullptr, head, value};

  // List is empty
  if (head) {
    head->prev = node;
  } else {
    tail = node;
  }

  head = node;
  ++_size;
}

void List::insert(Node* pos, int value) {
  if (pos == nullptr) {
    throw std::runtime_error("Incorrect position!");
  }
  bool contains_flag = false;
  for (auto cur = head; cur; cur = cur->next) {
    if (cur == pos) {
      contains_flag = true;
      break;
    }
  }
  if (!contains_flag) {
    throw std::runtime_error("Incorrect position!");
  }

  auto node = new Node{pos, pos->next, value};
  node->prev = node;
  pos->next = node;
  ++_size;
}

void List::pop_front() {
  if (!head) {
    throw std::runtime_error("Deleting in empty list");
  }

  auto to_delete = head;
  if (to_delete->next) {
    to_delete->next->prev = nullptr;
  } else {
    tail = nullptr;
  }
  head = to_delete->next;

  delete to_delete;
  --_size;
}

void List::pop_back() {
  if (!tail) {
    throw std::runtime_error("Deleting in empty list");
  }

  auto to_delete = tail;
  if (to_delete->prev) {
    to_delete->prev->next = nullptr;
  } else {
    head = nullptr;
  }
  tail = to_delete->prev;

  delete to_delete;
  --_size;
}

void List::erase(Node* pos) {
  if (!pos) {
    throw std::runtime_error("Incorrect position!");
  }

  if (pos->next) {
    pos->next->prev = pos->prev;
  }
  if (pos->prev) {
    pos->prev->next = pos->next;
  }
  if (pos == head) {
    head = pos->next;
  }
  if (pos == tail) {
    tail = pos->prev;
  }

  delete pos;
  --_size;
}

void List::clear() {
  auto cur = head;

  while (cur) {
    auto next = cur->next;
    delete cur;
    cur = next;
  }

  _size = 0;
  head = nullptr;
  tail = nullptr;
}

void List::reverse() {
  for (auto cur = head; cur; cur = cur->prev) {
    std::swap(cur->next, cur->prev);
  }

  std::swap(head, tail);
}

void List::remove_duplicates() {
  std::unordered_set<int> used{};
  auto cur = head;
  while (cur) {
    if (used.contains(cur->value)) {
      auto to_delete = cur;
      cur = to_delete->next;
      erase(to_delete);
    } else {
      used.insert(cur->value);
      cur = cur->next;
    }
  }
}

void List::replace(int old_value, int new_value) {
  for (auto cur = head; cur; cur = cur->next) {
    if (cur->value == old_value) {
      cur->value = new_value;
    }
  }
}

void List::merge(const List& other) {
  for (auto cur = other.head; cur; cur = cur->next) {
    push_back(cur->value);
  }
}

bool List::check_cycle() const {
  auto hare = head;
  auto tortoise = head;
  do {
    if (!hare || !hare->next) {
      return false;
    }
    hare = hare->next->next;
    tortoise = tortoise->next;
  } while (hare != tortoise);
  return true;
}

size_t List::size() const {
  return _size;
}

bool List::empty() const {
  return _size == 0;
}

void List::copy(const List& other) {
  clear();
  merge(other);
}
