#include <cassert>
#include <iostream>

#include "hashtable.h"

void test_insert_and_find() {
  HashTable<int, std::string> table;
  table.insert(1, "one");
  table.insert(2, "two");
  table.insert(3, "three");

  assert(table.find(1) != nullptr && *table.find(1) == "one");
  assert(table.find(2) != nullptr && *table.find(2) == "two");
  assert(table.find(3) != nullptr && *table.find(3) == "three");
  assert(table.find(4) == nullptr);
  std::cout << "1";
}

void test_erase() {
  HashTable<int, std::string> table;
  table.insert(1, "one");
  table.insert(2, "two");
  table.insert(3, "three");

  table.erase(2);
  assert(table.find(2) == nullptr);
  assert(table.find(1) != nullptr && *table.find(1) == "one");
  assert(table.find(3) != nullptr && *table.find(3) == "three");

  table.erase(1);
  assert(table.find(1) == nullptr);
  assert(table.find(3) != nullptr && *table.find(3) == "three");

  table.erase(3);
  assert(table.find(3) == nullptr);
  std::cout << "2";
}

void test_rehash() {
  HashTable<int, std::string> table(2, 0.5);
  table.insert(1, "one");
  table.insert(2, "two");
  table.insert(3, "three");

  assert(table.find(1) != nullptr && *table.find(1) == "one");
  assert(table.find(2) != nullptr && *table.find(2) == "two");
  assert(table.find(3) != nullptr && *table.find(3) == "three");
  std::cout << "3";
}

void test_operator_brackets() {
  HashTable<int, std::string> table;
  table.insert(1, "one");
  table.insert(2, "two");

  try {
    auto &node = table[table.find(1) - table.find(0)];
    assert(node.key == 1 && node.value == "one");
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  try {
    table[100];
  } catch (const std::out_of_range &e) {
    assert(std::string(e.what()) == "dumb user");
  } catch (...) {
    assert(false);
  }

  std::cout << "4";
}

void test_at() {
  HashTable<int, std::string> table;
  table.insert(1, "one");
  table.insert(2, "two");

  try {
    auto node = table.at(table.find(1) - table.find(0));
    assert(node.key == 1 && node.value == "one");
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  try {
    table.at(100);
  } catch (const std::out_of_range &e) {
    assert(std::string(e.what()) == "dumb user");
  } catch (...) {
    assert(false);
  }
  std::cout << "5";
}

int main() {
  test_insert_and_find();
  test_erase();
  test_rehash();
  test_operator_brackets();
  test_at();

  std::cout << "All tests passed!" << std::endl;
  return 0;
}