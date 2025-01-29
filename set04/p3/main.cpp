// #include <iostream>

// #include "avl_tree.h"

// int main() {
//   AVLTree tree{};
//   std::cout << tree.empty() << '\n';
//   tree.insert(2);
//   tree.insert(4);
//   tree.insert(6);
//   tree.insert(8);
//   tree.insert(10);
//   tree.insert(12);
//   tree.insert(14);
//   tree.insert(16);
//   tree.insert(18);
//   tree.insert(20);

//   auto array = tree.traversal();
//   for (int i = 0; i < 10; ++i) {
//     std::cout << array[i] << ' ';
//   }
//   std::cout << '\n';
//   delete[] array;

//   tree.erase(24);
//   tree.erase(10);
//   array = tree.traversal();
//   for (int i = 0; i < 9; ++i) {
//     std::cout << array[i] << ' ';
//   }
//   std::cout << '\n';
//   delete[] array;

//   tree.erase(16);
//   array = tree.traversal();
//   for (int i = 0; i < 8; ++i) {
//     std::cout << array[i] << ' ';
//   }
//   std::cout << '\n';
//   delete[] array;

//   // std::cout << tree.lowerBound(22);
//   for (int i = 19; i <= 50; ++i) {
//     auto lb = tree.lowerBound(i);
//     if (lb) {
//       std::cout << i << ' ' << *tree.lowerBound(i) << '\n';
//     } else {
//       std::cout << i << ' ' << "null\n";
//     }
//   }
// }

#include <iostream>

#include "avl_tree.h"

// Вспомогательная функция для проверки упорядоченности массива
bool isSorted(const int* array, int size) {
  for (int i = 1; i < size; ++i) {
    if (array[i - 1] > array[i]) {
      return false;
    }
  }
  return true;
}

// Вспомогательная функция для проверки условий
void assertTest(bool condition, const std::string& testName) {
  if (condition) {
    std::cout << "[PASSED] " << testName << std::endl;
  } else {
    std::cout << "[FAILED] " << testName << std::endl;
  }
}

int main() {
  // Тест конструктора по умолчанию
  {
    RandTree tree;
    assertTest(tree.empty(), "ConstructorDefault - Empty Tree");
    assertTest(tree.getSize() == 0, "ConstructorDefault - Size Zero");
    assertTest(tree.getRoot() == nullptr, "ConstructorDefault - Null Root");
  }

  // Тест конструктора с заданным значением
  {
    RandTree tree(10);
    assertTest(!tree.empty(), "ConstructorWithValue - Non-Empty Tree");
    assertTest(tree.getSize() == 1, "ConstructorWithValue - Size One");
    assertTest(tree.getRoot() != nullptr, "ConstructorWithValue - Non-Null Root");
    assertTest(tree.getRoot()->value == 10, "ConstructorWithValue - Root Value");
  }

  // Тест вставки одного значения
  {
    RandTree tree;
    tree.insert(5);
    assertTest(!tree.empty(), "InsertSingleValue - Non-Empty Tree");
    assertTest(tree.getSize() == 1, "InsertSingleValue - Size One");
    assertTest(tree.getRoot()->value == 5, "InsertSingleValue - Root Value");
  }

  // Тест вставки нескольких значений
  {
    RandTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);

    assertTest(tree.getSize() == 3, "InsertMultipleValues - Size Three");

    int* traversal = tree.traversal();
    assertTest(isSorted(traversal, tree.getSize()), "InsertMultipleValues - Sorted");
  }

  // Тест удаления одного значения
  {
    RandTree tree(10);
    tree.erase(10);
    assertTest(tree.empty(), "EraseSingleValue - Empty Tree");
    assertTest(tree.getSize() == 0, "EraseSingleValue - Size Zero");
    assertTest(tree.getRoot() == nullptr, "EraseSingleValue - Null Root");
  }

  // Тест удаления нескольких значений
  {
    RandTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.erase(10);

    assertTest(tree.getSize() == 2, "EraseMultipleValues - Size Two");

    int* traversal = tree.traversal();
    assertTest(isSorted(traversal, tree.getSize()), "EraseMultipleValues - Sorted");
  }

  // Тест поиска существующего значения
  {
    RandTree tree;
    tree.insert(15);
    int* value = tree.find(15);
    assertTest(value != nullptr, "FindExistingValue - Not Null");
    assertTest(*value == 15, "FindExistingValue - Correct Value");
  }

  // Тест поиска несуществующего значения
  {
    RandTree tree;
    tree.insert(10);
    int* value = tree.find(20);
    assertTest(value == nullptr, "FindNonExistingValue - Null");
  }

  // Тест lowerBound для существующего значения
  {
    RandTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);

    int* value = tree.lowerBound(10);
    assertTest(value != nullptr, "LowerBoundExistingValue - Not Null");
    assertTest(*value == 10, "LowerBoundExistingValue - Correct Value");
  }

  // Тест lowerBound для несуществующего значения
  {
    RandTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);

    int* value = tree.lowerBound(15);
    assertTest(value != nullptr, "LowerBoundNonExistingValue - Not Null");
    assertTest(*value == 20, "LowerBoundNonExistingValue - Correct Value");
  }

  // Тест пустого дерева
  {
    RandTree tree;
    assertTest(tree.empty(), "EmptyTree - Empty Tree");
    assertTest(tree.getSize() == 0, "EmptyTree - Size Zero");
    assertTest(tree.find(10) == nullptr, "EmptyTree - Find Null");
    assertTest(tree.lowerBound(10) == nullptr, "EmptyTree - LowerBound Null");
  }

  return 0;
}
