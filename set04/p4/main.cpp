// #include <algorithm>
// #include <cassert>
// #include <functional>
// #include <iostream>

// #include "rbtree.h"

// // Вспомогательная структура для передачи результатов проверки
// struct ValidationResult {
//   bool isValid;     // Соответствует ли дерево правилам
//   int blackHeight;  // Высота черных узлов
// };

// // Валидация узла и его поддерев
// ValidationResult validateNode(Node* node) {
//   if (!node) {
//     // Пустой узел имеет черную высоту 1
//     return {true, 1};
//   }

//   // Узел должен быть либо красным, либо черным
//   if (node->color != Color::RED && node->color != Color::BLACK) {
//     return {false, 0};
//   }

//   // Проверка детей
//   ValidationResult left = validateNode(node->left);
//   ValidationResult right = validateNode(node->right);

//   // Если одно из поддерев недопустимо, всё дерево недопустимо
//   if (!left.isValid || !right.isValid) {
//     return {false, 0};
//   }

//   // Левое и правое поддеревья должны иметь одинаковую черную высоту
//   if (left.blackHeight != right.blackHeight) {
//     return {false, 0};
//   }

//   // Если узел красный, его дети должны быть черными
//   if (node->color == Color::RED) {
//     if ((node->left && node->left->color == Color::RED) || (node->right && node->right->color == Color::RED)) {
//       return {false, 0};
//     }
//   }

//   // Черная высота увеличивается на 1, если текущий узел черный
//   int blackHeight = left.blackHeight + (node->color == Color::BLACK ? 1 : 0);

//   return {true, blackHeight};
// }

// // Проверка всего дерева
// bool validateRBTree(RBTree& tree) {
//   if (!tree.root) {
//     return true;  // Пустое дерево всегда корректно
//   }

//   // Корень должен быть черным
//   if (tree.root->color != Color::BLACK) {
//     return false;
//   }

//   // Проверяем остальные свойства дерева
//   ValidationResult result = validateNode(tree.root);
//   return result.isValid;
// }

// // Проверка содержимого массива
// bool arraysEqual(const int* array, const std::vector<int>& expected, int size) {
//   if (size != static_cast<int>(expected.size())) {
//     return false;
//   }
//   for (int i = 0; i < size; ++i) {
//     if (array[i] != expected[i]) {
//       return false;
//     }
//   }
//   return true;
// }

// // Вспомогательная функция для проверки условий
// void assertTest(bool condition, const std::string& testName) {
//   if (condition) {
//     std::cout << "[PASSED] " << testName << std::endl;
//   } else {
//     std::cout << "[FAILED] " << testName << std::endl;
//   }
// }

// std::pair<int*, int> traversal(Node* root) {
//   std::vector<int> keys;

//   // Вспомогательная функция для рекурсивного обхода
//   std::function<void(Node*)> inOrder = [&](Node* node) {
//     if (!node)
//       return;
//     inOrder(node->left);
//     keys.push_back(node->key);
//     inOrder(node->right);
//   };

//   inOrder(root);

//   // Копируем ключи в динамический массив
//   int* result = new int[keys.size()];
//   std::copy(keys.begin(), keys.end(), result);

//   return {result, static_cast<int>(keys.size())};
// }

// int main() {
//   // Тест конструктора по умолчанию
//   {
//     RBTree tree;
//     assertTest(tree.empty(), "DefaultConstructor - Empty Tree");
//     assertTest(tree.size() == 0, "DefaultConstructor - Size Zero");
//     assertTest(tree.root == nullptr, "DefaultConstructor - Null Root");
//   }

//   // Тест конструктора с initializer_list
//   {
//     RBTree tree{10, 20, 5};
//     assertTest(!tree.empty(), "InitializerListConstructor - Non-Empty Tree");
//     assertTest(tree.size() == 3, "InitializerListConstructor - Size Three");

//     int* lb = tree.lowerBound(10);
//     assertTest(lb != nullptr, "InitializerListConstructor - LowerBound Found");
//     assertTest(*lb == 10, "InitializerListConstructor - LowerBound Correct");
//   }

//   // Тест вставки одного значения
//   {
//     RBTree tree;
//     tree.insert(15);
//     assertTest(!tree.empty(), "InsertSingleValue - Non-Empty Tree");
//     assertTest(tree.size() == 1, "InsertSingleValue - Size One");

//     int* found = tree.find(15);
//     assertTest(found != nullptr, "InsertSingleValue - Find Non-Null");
//     assertTest(*found == 15, "InsertSingleValue - Find Correct");
//   }

//   // Тест вставки нескольких значений
//   {
//     RBTree tree;
//     tree.insert(10);
//     tree.insert(20);
//     tree.insert(5);

//     assertTest(tree.size() == 3, "InsertMultipleValues - Size Three");

//     int* lb = tree.lowerBound(10);
//     assertTest(lb != nullptr, "InsertMultipleValues - LowerBound Found");
//     assertTest(*lb == 10, "InsertMultipleValues - LowerBound Correct");
//   }

//   // Тест поиска существующего значения
//   {
//     RBTree tree{10, 20, 30};
//     int* found = tree.find(20);
//     assertTest(found != nullptr, "FindExistingValue - Non-Null");
//     assertTest(*found == 20, "FindExistingValue - Correct Value");
//   }

//   // Тест поиска несуществующего значения
//   {
//     RBTree tree{10, 20, 30};
//     int* found = tree.find(25);
//     assertTest(found == nullptr, "FindNonExistingValue - Null");
//   }

//   // Тест lowerBound для существующего значения
//   {
//     RBTree tree{10, 20, 30};
//     int* lb = tree.lowerBound(20);
//     assertTest(lb != nullptr, "LowerBoundExistingValue - Non-Null");
//     assertTest(*lb == 20, "LowerBoundExistingValue - Correct Value");
//   }

//   // Тест lowerBound для несуществующего значения
//   {
//     RBTree tree{10, 20, 30};
//     int* lb = tree.lowerBound(25);
//     assertTest(lb != nullptr, "LowerBoundNonExistingValue - Non-Null");
//     assertTest(*lb == 30, "LowerBoundNonExistingValue - Correct Value");
//   }

//   // Тест пустого дерева
//   {
//     RBTree tree;
//     assertTest(tree.empty(), "EmptyTree - Empty");
//     assertTest(tree.size() == 0, "EmptyTree - Size Zero");
//     assertTest(tree.find(10) == nullptr, "EmptyTree - Find Null");
//     assertTest(tree.lowerBound(10) == nullptr, "EmptyTree - LowerBound Null");
//   }

//   // Тест обхода пустого дерева
//   {
//     RBTree tree;
//     auto [keys, size] = traversal(tree.root);
//     assertTest(size == 0, "TraversalEmptyTree - Size Zero");
//     assertTest(keys == nullptr, "TraversalEmptyTree - Null Keys");
//     delete[] keys;
//   }

//   // Тест обхода дерева с одним элементом
//   {
//     RBTree tree{10};
//     auto [keys, size] = traversal(tree.root);
//     assertTest(size == 1, "TraversalSingleNode - Size One");
//     assertTest(keys != nullptr, "TraversalSingleNode - Non-Null Keys");
//     assertTest(arraysEqual(keys, {10}, size), "TraversalSingleNode - Correct Keys");
//     delete[] keys;
//   }

//   // Тест обхода дерева с несколькими элементами
//   {
//     RBTree tree{20, 10, 30, 15, 25};
//     auto [keys, size] = traversal(tree.root);
//     assertTest(size == 5, "TraversalMultipleNodes - Size Five");
//     assertTest(arraysEqual(keys, {10, 15, 20, 25, 30}, size), "TraversalMultipleNodes - Correct Keys");
//     delete[] keys;
//   }

//   // Тест обхода дерева после вставки
//   {
//     RBTree tree;
//     tree.insert(50);
//     tree.insert(20);
//     tree.insert(70);
//     tree.insert(10);
//     tree.insert(30);

//     auto [keys, size] = traversal(tree.root);
//     assertTest(size == 5, "TraversalAfterInsert - Size Five");
//     assertTest(arraysEqual(keys, {10, 20, 30, 50, 70}, size), "TraversalAfterInsert - Correct Keys");
//     delete[] keys;
//   }

//   // Тест обхода дерева после удаления
//   {
//     RBTree tree{50, 20, 70, 10, 30};
//     tree.insert(60);
//     tree.insert(80);

//     auto [keys, size] = traversal(tree.root);
//     assertTest(size == 7, "TraversalAfterErase - Size Six");
//     assertTest(arraysEqual(keys, {10, 20, 30, 50, 60, 70, 80}, size), "TraversalAfterErase - Correct Keys");
//     delete[] keys;
//   }

//   // Тест дерева с одинаковыми элементами
//   {
//     RBTree tree;
//     tree.insert(10);
//     tree.insert(10);
//     tree.insert(10);

//     auto [keys, size] = traversal(tree.root);
//     assertTest(size == 1, "TraversalDuplicateValues - Size Three");
//     assertTest(arraysEqual(keys, {10}, size), "TraversalDuplicateValues - Correct Keys");
//   }

//   // Тест глубоко вложенного дерева (вставка по возрастанию)
//   {
//     RBTree tree;
//     for (int i = 1; i <= 10; ++i) {
//       tree.insert(i);
//     }

//     auto [keys, size] = traversal(tree.root);
//     assertTest(tree.size() == 10, "jkbnfalsjkdbnfkjaldsbfkadsjbfasjdkfbasdkfljb");
//     assertTest(size == 10, "TraversalDeepTree - Size Ten");
//     assertTest(arraysEqual(keys, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, size), "TraversalDeepTree - Correct Keys");
//   }

//   // Тест глубоко вложенного дерева (вставка по убыванию)
//   {
//     RBTree tree;
//     for (int i = 10; i >= 1; --i) {
//       tree.insert(i);
//     }

//     auto [keys, size] = traversal(tree.root);
//     assertTest(size == 10, "TraversalReverseDeepTree - Size Ten");
//     assertTest(arraysEqual(keys, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, size), "TraversalReverseDeepTree - Correct Keys");
//   }

//   // Тест с повторной вставкой и удалением
//   {
//     RBTree tree;
//     tree.insert(20);
//     tree.insert(10);
//     tree.insert(30);

//     tree.insert(25);
//     tree.insert(35);

//     auto [keys, size] = traversal(tree.root);
//     assertTest(size == 5, "TraversalAfterErase - Size Four");
//     assertTest(arraysEqual(keys, {10, 20, 25, 30, 35}, size), "TraversalAfterErase - Correct Keys");
//   }

//   // // Тест на пустое дерево
//   // {
//   //   RBTree tree;
//   //   assertTest(validateRBTree(tree), "ValidateEmptyTree");
//   // }

//   // Тест дерева с одним элементом
//   {
//     RBTree tree{10};
//     assertTest(validateRBTree(tree), "ValidateSingleNodeTree");
//   }

//   // Тест после вставки элементов
//   {
//     RBTree tree{20, 10, 30, 5, 15, 25, 35};
//     assertTest(validateRBTree(tree), "ValidateAfterInsert");
//   }

//   // Тест после удаления элементов
//   {
//     RBTree tree{20, 10, 30, 5, 15, 25, 35};
//     assertTest(validateRBTree(tree), "ValidateAfterErase");
//   }

//   // Тест на глубокое дерево
//   {
//     RBTree tree;
//     for (int i = 1; i <= 50; ++i) {
//       tree.insert(i);
//     }
//     assertTest(validateRBTree(tree), "ValidateDeepTree");
//   }

//   // Тест на большое дерево
//   {
//     RBTree tree;
//     for (int i = 1; i <= 1000; ++i) {
//       tree.insert(i);
//     }
//     assertTest(validateRBTree(tree), "ValidateLargeTree");
//   }

//   {
//     RBTree tree;
//     for (int i = 1; i <= 10; ++i) {
//       tree.insert(i);
//     }
//     assertTest(validateRBTree(tree), "ValidateLargeTree");
//   }

//   {
//     RBTree tree;
//     int n = 10;
//     std::vector<int> vec{};
//     for (int i = 0; i < n; ++i) {
//       int rnd = rand() % 100000;
//       tree.insert(rnd);
//       vec.push_back(rnd);
//     }

//     std::sort(vec.begin(), vec.end());

//     for (int i = 0; i < n; ++i) {
//       std::cout << vec[i] << ' ';
//     }
//     std::cout << '\n';

//     auto [keys, size] = traversal(tree.root);
//     assertTest(size == n, "Random size");
//     assertTest(arraysEqual(keys, vec, size), "random - Correct Keys");
//     delete[] keys;
//   }

//   return 0;
// }

#include <cassert>
#include <iostream>

#include "rbtree.h"

// Вспомогательная функция для проверки свойств красно-черного дерева
bool verifyRBTreeProperties(Node* node, int& blackHeight) {
  if (!node) {
    blackHeight = 1;  // NULL-узел считается черным
    return true;
  }

  int leftBlackHeight = 0, rightBlackHeight = 0;

  // Рекурсивно проверяем свойства поддеревьев
  if (!verifyRBTreeProperties(node->left, leftBlackHeight))
    return false;
  if (!verifyRBTreeProperties(node->right, rightBlackHeight))
    return false;

  // Свойство 5: черная высота должна быть одинаковой
  if (leftBlackHeight != rightBlackHeight)
    return false;

  // Свойство 4: красные узлы не должны иметь красных потомков
  if (node->color == Color::RED) {
    if ((node->left && node->left->color == Color::RED) || (node->right && node->right->color == Color::RED)) {
      return false;
    }
  }

  // Увеличиваем черную высоту, если узел черный
  blackHeight = leftBlackHeight + (node->color == Color::BLACK ? 1 : 0);
  return true;
}

// Проверка: Пустое дерево
void testEmptyTree() {
  RBTree tree;
  assert(tree.size() == 0);
  assert(tree.empty());
  assert(tree.root == nullptr);
  std::cout << "testEmptyTree passed\n";
}

// Проверка: Вставка элементов и поиск
void testInsertAndFind() {
  RBTree tree;
  tree.insert(10);
  tree.insert(20);
  tree.insert(5);

  assert(tree.size() == 3);
  assert(!tree.empty());

  int* val = tree.find(10);
  assert(val != nullptr && *val == 10);

  val = tree.find(15);
  assert(val == nullptr);  // Элемента 15 нет в дереве

  std::cout << "testInsertAndFind passed\n";
}

// Проверка: LowerBound
void testLowerBound() {
  RBTree tree = {5, 10, 15};
  int* val = tree.lowerBound(8);
  assert(val != nullptr && *val == 10);

  val = tree.lowerBound(15);
  assert(val != nullptr && *val == 15);

  val = tree.lowerBound(16);
  assert(val == nullptr);  // Нет большего или равного 16

  std::cout << "testLowerBound passed\n";
}

// Проверка: Свойства красно-черного дерева
void testRBTreeProperties() {
  RBTree tree = {10, 20, 30, 40, 50, 25};
  int blackHeight = 0;
  assert(verifyRBTreeProperties(tree.root, blackHeight));
  assert(blackHeight > 0);  // Черная высота должна быть положительной
  std::cout << "testRBTreeProperties passed\n";
}

// Проверка: Размеры и черная высота
void testSizeAndHeight() {
  RBTree tree = {10, 20, 30};
  assert(tree.size() == 3);

  int blackHeight = 0;
  assert(verifyRBTreeProperties(tree.root, blackHeight));
  assert(blackHeight > 0);

  std::cout << "testSizeAndHeight passed\n";
}

// Проверка: Удаление дерева
void testTreeDestruction() {
  RBTree* tree = new RBTree({10, 20, 30});
  delete tree;  // Если тут все корректно, утечек не будет
  std::cout << "testTreeDestruction passed\n";
}

// Вспомогательная функция для проверки корректности поля size
int verifySize(Node* node) {
  if (!node)
    return 0;
  int expectedSize = 1 + verifySize(node->left) + verifySize(node->right);
  assert(node->size == expectedSize);
  return expectedSize;
}

// Вспомогательная функция для проверки корректности черной высоты
int verifyBlackHeight(Node* node) {
  if (!node)
    return 1;  // NULL-узлы считаются черными

  int leftBlackHeight = verifyBlackHeight(node->left);
  int rightBlackHeight = verifyBlackHeight(node->right);

  // Черная высота поддеревьев должна быть одинаковой
  assert(leftBlackHeight == rightBlackHeight);

  // Черная высота поддерева текущего узла
  int subtreeBlackHeight = leftBlackHeight;

  // Проверка, что поле height соответствует черной высоте поддерева
  assert(node->height == subtreeBlackHeight);

  // Возвращаем черную высоту, добавляя 1, если текущий узел черный
  return subtreeBlackHeight + (node->color == Color::BLACK ? 1 : 0);
}

// Проверка: Свойства узлов дерева
void verifyNodeProperties(Node* node) {
  if (!node)
    return;

  // Проверяем размер поддерева
  verifySize(node);

  // Проверяем черную высоту
  // int blackHeight = verifyBlackHeight(node);
  // assert(node->height == blackHeight);

  // Рекурсивно проверяем потомков
  verifyNodeProperties(node->left);
  verifyNodeProperties(node->right);
}

// Проверка: Вставка большого количества элементов
void testLargeTree() {
  const int N = 1000;
  RBTree tree;

  // Вставляем элементы
  for (int i = 1; i <= N; ++i) {
    tree.insert(i);
  }

  // Проверяем размер дерева
  assert(tree.size() == N);

  // Проверяем свойства дерева
  verifyNodeProperties(tree.root);

  std::cout << "testLargeTree passed\n";
}

// Проверка: Вставка элементов в произвольном порядке
void testRandomInsertions() {
  int keys[] = {50, 20, 70, 10, 30, 60, 80, 5, 15, 25, 35};
  RBTree tree;

  for (int key : keys) {
    tree.insert(key);
  }

  // Проверяем размер дерева
  assert(tree.size() == 11);

  // Проверяем свойства дерева
  verifyNodeProperties(tree.root);

  std::cout << "testRandomInsertions passed\n";
}

// Проверка: Большое дерево с повторной проверкой черной высоты
void testLargeBalancedTree() {
  RBTree tree;

  // Добавляем элементы
  for (int i = 100; i <= 200; ++i) {
    tree.insert(i);
  }
  for (int i = 50; i < 100; ++i) {
    tree.insert(i);
  }

  // Проверяем размер
  assert(tree.size() == 151);

  // Проверяем свойства дерева
  verifyNodeProperties(tree.root);

  std::cout << "testLargeBalancedTree passed\n";
}

// Проверка: Большое дерево с повторной проверкой черной высоты
void testLargeBalancedTree2() {
  RBTree tree;

  // Добавляем элементы
  for (int i = 100; i <= 1000; ++i) {
    tree.insert(i);
  }
  for (int i = 100; i >= 0; --i) {
    tree.insert(i);
  }

  // Проверяем размер
  assert(tree.size() == 901 + 100);

  // Проверяем свойства дерева
  verifyNodeProperties(tree.root);

  std::cout << "testLargeBalancedTree passed\n";
}

int main() {
  try {
    testEmptyTree();
    testInsertAndFind();
    testLowerBound();
    testRBTreeProperties();
    testSizeAndHeight();
    testTreeDestruction();
    testLargeTree();
    testRandomInsertions();
    testLargeBalancedTree();
    testLargeBalancedTree2();

    std::cout << "All tests passed successfully!\n";
  } catch (const std::exception& e) {
    std::cerr << "Test failed: " << e.what() << '\n';
  } catch (...) {
    std::cerr << "Unknown error occurred during testing.\n";
  }
}
