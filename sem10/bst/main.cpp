#include <cassert>
#include <iostream>

#include "tree.h"

void TestInsertAndFind() {
  BinarySearchTree<int> tree;
  tree.Insert(5);
  tree.Insert(3);
  tree.Insert(7);
  tree.Insert(2);
  tree.Insert(4);
  assert(tree.FindMin() == 2 && "TestInsertAndFind: FindMin failed");
  assert(tree.FindMax() == 7 && "TestInsertAndFind: FindMax failed");
  assert(tree.Contains(5) && "TestInsertAndFind: Contains failed");
  assert(!tree.Contains(6) && "TestInsertAndFind: Contains failed");
}

void TestRemove() {
  BinarySearchTree<int> tree;
  tree.Insert(5);
  tree.Insert(3);
  tree.Insert(7);
  tree.Remove(5);
  assert(!tree.Contains(5) && "TestRemove: Contains failed");
}

void TestTraversal() {
  BinarySearchTree<int> tree;
  tree.Insert(5);
  tree.Insert(3);
  tree.Insert(7);
  tree.Insert(2);
  tree.Insert(4);
  std::vector<int> expected = {2, 3, 4, 5, 7};
  std::vector<int> result;
  for (const auto &x : tree) {
    result.push_back(x);
  }
  assert(result == expected && "TestTraversal: In-order traversal failed");
}

void TestEmptyTreeTraversal() {
  BinarySearchTree<int> tree;
  std::vector<int> result;
  for (const auto &x : tree) {
    result.push_back(x);
  }
  assert(result.empty() && "TestEmptyTreeTraversal: Traversal of empty tree failed");
}

void TestSingleElementTraversal() {
  BinarySearchTree<int> tree;
  tree.Insert(42);
  std::vector<int> expected = {42};
  std::vector<int> result;
  for (const auto &x : tree) {
    result.push_back(x);
  }
  assert(result == expected && "TestSingleElementTraversal: Traversal of single element tree failed");
}

void TestLeftHeavyTreeTraversal() {
  BinarySearchTree<int> tree;
  tree.Insert(5);
  tree.Insert(4);
  tree.Insert(3);
  tree.Insert(2);
  tree.Insert(1);
  std::vector<int> expected = {1, 2, 3, 4, 5};
  std::vector<int> result;
  for (const auto &x : tree) {
    result.push_back(x);
  }
  assert(result == expected && "TestLeftHeavyTreeTraversal: In-order traversal of left-heavy tree failed");
}

void TestRightHeavyTreeTraversal() {
  BinarySearchTree<int> tree;
  tree.Insert(1);
  tree.Insert(2);
  tree.Insert(3);
  tree.Insert(4);
  tree.Insert(5);
  std::vector<int> expected = {1, 2, 3, 4, 5};
  std::vector<int> result;
  for (const auto &x : tree) {
    result.push_back(x);
  }
  assert(result == expected && "TestRightHeavyTreeTraversal: In-order traversal of right-heavy tree failed");
}

int main() {
  TestInsertAndFind();
  TestRemove();
  TestTraversal();
  TestEmptyTreeTraversal();
  TestSingleElementTraversal();
  TestLeftHeavyTreeTraversal();
  TestRightHeavyTreeTraversal();
  std::cout << "All tests passed!" << std::endl;
  return 0;
}