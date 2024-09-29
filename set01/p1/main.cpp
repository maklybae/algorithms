#include <iostream>

#include "list.h"

void test_check_cycle() {
  List list;

  // Test 1: Empty list
  if (list.check_cycle()) {
    std::cout << "Test 1 failed: Empty list should not have a cycle.\n";
  } else {
    std::cout << "Test 1 passed.\n";
  }

  // Test 2: Single node list without cycle
  list.push_back(1);
  if (list.check_cycle()) {
    std::cout << "Test 2 failed: Single node list should not have a cycle.\n";
  } else {
    std::cout << "Test 2 passed.\n";
  }

  // Test 3: Multiple nodes list without cycle
  list.push_back(2);
  list.push_back(3);
  if (list.check_cycle()) {
    std::cout << "Test 3 failed: Multiple nodes list should not have a cycle.\n";
  } else {
    std::cout << "Test 3 passed.\n";
  }

  // Test 4: List with a cycle
  auto head = list.head;
  auto tail = list.tail;
  tail->next = head;  // Creating a cycle
  if (list.check_cycle()) {
    std::cout << "Test 4 passed.\n";
  } else {
    std::cout << "Test 4 failed: List with a cycle should be detected.\n";
  }

  // Clean up the cycle for further tests
  tail->next = nullptr;
}

int main() {
  test_check_cycle();
  return 0;
}