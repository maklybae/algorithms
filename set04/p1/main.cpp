#include <algorithm>
#include <iostream>

template <typename Comparable>
class BinarySearchTree {
 private:
  struct BinaryNode {
    BinaryNode *parent;
    BinaryNode *left;
    BinaryNode *right;
    long long height;
    Comparable element;

    BinaryNode(const Comparable &element, BinaryNode *parent, BinaryNode *lt, BinaryNode *rt)
        : element{element}, parent{parent}, left{lt}, right{rt}, height{0} {
    }
  };

  BinaryNode *root_;

  static long long Height(BinaryNode *t) {
    if (!t) {
      return -1;
    }
    return t->height;
  }

  static void MakeEmpty(BinaryNode *&t) {
    if (t) {
      MakeEmpty(t->left);
      MakeEmpty(t->right);
      delete t;
    }
    t = nullptr;
  }

  static void Insert(Comparable x, BinaryNode *&t, BinaryNode *parent) {
    if (!t) {
      t = new BinaryNode{x, parent, nullptr, nullptr};
    } else if (x < t->element) {
      Insert(x, t->left, t);
    } else if (t->element < x) {
      Insert(x, t->right, t);
    }
    t->height = std::max(Height(t->left), Height(t->right)) + 1;
  }

  static bool CheckAVL(BinaryNode *t) {
    if (!t) {
      return true;
    }

    long long balanced = Height(t->left) - Height(t->right);
    return std::abs(balanced) <= 1 && CheckAVL(t->left) && CheckAVL(t->right);
  }

 public:
  void Insert(Comparable x) {
    Insert(x, root_, nullptr);
  }

  bool CheckAVL() {
    return CheckAVL(root_);
  }

  ~BinarySearchTree() {
    MakeEmpty(root_);
  }
};

int main() {
  BinarySearchTree<int> tree{};

  int key{};
  std::cin >> key;
  while (key != 0) {
    tree.Insert(key);
    std::cin >> key;
  }

  if (tree.CheckAVL()) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }
}