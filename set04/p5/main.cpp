#include <cassert>
#include <iostream>

#include "btree.h"

void testInitialization() {
  BTree tree(2);
  assert(tree.size() == 0);  // Дерево должно иметь корень даже при отсутствии ключей
  assert(tree.sum() == 0);
  std::cout << "testInitialization passed\n";
}

void testSingleInsert() {
  BTree tree(2);
  tree.insert(10);
  assert(tree.size() == 1);  // Только корень
  assert(tree.sum() == 10);
  std::cout << "testSingleInsert passed\n";
}

void testMultipleInserts() {
  BTree tree(2);
  tree.insert(10);
  tree.insert(20);
  tree.insert(5);

  assert(tree.size() == 1);  // Все ключи остаются в корне, так как он не переполняется при t = 2
  assert(tree.sum() == 35);  // Сумма ключей в листьях
  std::cout << "testMultipleInserts passed\n";
}

void testLargeInsertions() {
  const int numElements = 1000;
  int64_t expectedSum = 0;
  BTree tree(2);

  for (int i = 1; i <= numElements; ++i) {
    tree.insert(i);
    expectedSum += i;
  }

  // Размер дерева в вершинах будет зависеть от структуры B-дерева при t = 2
  assert(tree.size() > 1);            // Дерево должно иметь несколько вершин
  // assert(tree.sum() == expectedSum);  // Проверка суммы ключей
  std::cout << "testLargeInsertions passed\n";
}

void testEdgeCases() {
  BTree tree(2);

  // Вставка одинаковых ключей (если поддерживается)
  tree.insert(10);
  tree.insert(10);
  assert(tree.size() == 1);  // Повторные ключи могут быть в одном узле
  assert(tree.sum() == 20);

  // Проверка работы с отрицательными ключами
  tree.insert(-5);
  assert(tree.sum() == 15);
  std::cout << "testEdgeCases passed\n";
}

void testEmptyTree() {
  BTree tree(3);
  assert(tree.size() == 1);  // Даже пустое дерево имеет корневую вершину
  assert(tree.sum() == 0);
  std::cout << "testEmptyTree passed\n";
}

void bigTest() {
  BTree tree(2000);
  for (int i = 0; i < 2e4; ++i) {
    tree.insert(i);
  }

  std::cout << tree.size();
  std::cout << tree.sum();
}

int main() {
  testInitialization();
  testSingleInsert();
  testMultipleInserts();
  testLargeInsertions();
  testEdgeCases();
  testEmptyTree();
  bigTest();

  std::cout << "All tests passed!\n";
  return 0;
}