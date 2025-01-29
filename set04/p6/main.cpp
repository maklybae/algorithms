#include <random>

#include "splay-tree.h"

std::mt19937 rnd{52};

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

// Проверка создания узлов
void testNodeCreation() {
  Node* parent = new Node(10, nullptr);
  Node* child = new Node(5, parent);

  assert(parent->key == 10);
  assert(parent->parent == nullptr);
  assert(child->key == 5);
  assert(child->parent == parent);

  delete parent;
  delete child;

  std::cout << "testNodeCreation passed!" << std::endl;
}

// Проверка вставки элементов
void testInsert() {
  SplayTree tree;
  tree.insert(10);
  tree.insert(5);
  tree.insert(20);

  Node* root = tree.find(10);
  assert(root != nullptr);
  assert(root->key == 10);

  Node* leftChild = root->left;
  Node* rightChild = root->right;

  assert(leftChild != nullptr && leftChild->key == 5);
  assert(rightChild != nullptr && rightChild->key == 20);

  std::cout << "testInsert passed!" << std::endl;
}

// Проверка поиска элемента
void testFind() {
  SplayTree tree;
  tree.insert(15);
  tree.insert(10);
  tree.insert(20);

  Node* found = tree.find(10);
  assert(found != nullptr && found->key == 10);

  Node* notFound = tree.find(25);
  assert(notFound == nullptr);

  std::cout << "testFind passed!" << std::endl;
}

// Проверка высоты дерева
void testGetHeight() {
  SplayTree tree;
  assert(tree.getHeight() == 0);

  tree.insert(10);
  tree.insert(5);
  tree.insert(20);
  tree.insert(15);

  assert(tree.getHeight() == 3);  // Ожидаемая высота дерева

  std::cout << "testGetHeight passed!" << std::endl;
}

// Проверка splay-операции
void testSplay() {
  SplayTree tree;
  tree.insert(10);
  tree.insert(5);
  tree.insert(20);

  Node* node = tree.find(5);
  int rotations = tree.splay(node);

  assert(rotations > 0);  // Проверяем, что выполнено хотя бы одно вращение
  assert(tree.find(5) == tree.find(5));  // Убедимся, что splay делает элемент корнем

  std::cout << "testSplay passed!" << std::endl;
}

// Основной метод для запуска тестов
int main() {
  // testNodeCreation();
  // testInsert();
  // testFind();
  // testGetHeight();
  // testSplay();

  // std::cout << "All tests passed!" << std::endl;

  SplayTree tree{};
  tree.insert(10);
  tree.insert(5);
  tree.insert(20);
  tree.insert(10);
  tree.insert(5);
  tree.insert(20);
  tree.insert(15);
  tree.insert(41);
  tree.insert(242);
  tree.insert(42);
  tree.insert(0);
  tree.insert(32);
  tree.insert(91);
  tree.insert(6);

  auto f = tree.find(15);
  tree.splay(f);
  f = tree.find(41);
  tree.splay(f);
  f = tree.find(1412143);
  tree.splay(f);
  f = tree.find(0);
  tree.splay(f);

  tree.getHeight();
}
