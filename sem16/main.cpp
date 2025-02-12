#include <chrono>
#include <iostream>
#include <random>
#include <vector>

struct AVLNode {
  int height;
  AVLNode *left;
  AVLNode *right;
  int value;

  AVLNode(int value);

  ~AVLNode();
};

class AVLTree {
 public:
  AVLTree();

  explicit AVLTree(int value);

  int getHeight();

  void insert(int value);

  void erase(int value);

  int *find(int value);

  int *traversal();

  int *lowerBound(int value);

  bool empty();

  AVLNode *getRoot();

  int getSize();

  ~AVLTree();

 private:
  AVLNode *root_;
  int size_;

  int getNodeHeight(AVLNode *node);

  int balanceFactor(AVLNode *node);

  void update(AVLNode *node);

  AVLNode *rotateRight(AVLNode *node);

  AVLNode *rotateLeft(AVLNode *node);

  AVLNode *balanceNode(AVLNode *node);

  AVLNode *insertNode(AVLNode *node, int value);

  AVLNode *findMinNode(AVLNode *node);

  AVLNode *removeMinNode(AVLNode *node);

  AVLNode *removeNode(AVLNode *node, int value);

  AVLNode *findNode(AVLNode *node, int value);

  void traversalInternal(AVLNode *node, int *array, int *index);

  AVLNode *lowerBoundInternal(AVLNode *current, int value) const;
};

AVLNode::AVLNode(int value) : height{0}, left{nullptr}, right{nullptr}, value{value} {
}

AVLNode::~AVLNode() = default;

AVLTree::AVLTree() : root_{nullptr}, size_{0} {
}

AVLTree::AVLTree(int value) {
  root_ = new AVLNode{value};
  size_ = 1;
}

int AVLTree::getHeight() {
  return getNodeHeight(root_) + 1;
}

void AVLTree::insert(int value) {
  root_ = insertNode(root_, value);
}

void AVLTree::erase(int value) {
  root_ = removeNode(root_, value);
}

int *AVLTree::find(int value) {
  auto node = findNode(root_, value);
  if (!node) {
    return nullptr;
  }
  return &node->value;
}

int *AVLTree::traversal() {
  int *array = new int[size_];
  int *index = new int;
  *index = 0;

  traversalInternal(root_, array, index);
  return array;
}

int *AVLTree::lowerBound(int value) {
  auto node = lowerBoundInternal(root_, value);
  if (!node) {
    return nullptr;
  }
  return &node->value;
}

bool AVLTree::empty() {
  return size_ == 0;
}

AVLNode *AVLTree::getRoot() {
  return root_;
}

int AVLTree::getSize() {
  return size_;
}

void clear(AVLNode *&node) {
  if (node) {
    clear(node->left);
    clear(node->right);
    delete node;
    node = nullptr;
  }
}

AVLTree::~AVLTree() {
  clear(root_);
}

int AVLTree::getNodeHeight(AVLNode *node) {
  if (!node) {
    return -1;
  }
  return node->height;
}

int AVLTree::balanceFactor(AVLNode *node) {
  return getNodeHeight(node->left) - getNodeHeight(node->right);
}

void AVLTree::update(AVLNode *node) {  // ???? что этот метод должен делать ????
  if (!node) {
    return;
  }
  node->height = std::max(getNodeHeight(node->left), getNodeHeight(node->right)) + 1;
}

AVLNode *AVLTree::rotateRight(AVLNode *node) {
  auto current = node->left;
  node->left = current->right;
  current->right = node;
  node->height = std::max(getNodeHeight(node->left), getNodeHeight(node->right)) + 1;
  current->height = std::max(getNodeHeight(current->left), node->height) + 1;
  return current;
}

AVLNode *AVLTree::rotateLeft(AVLNode *node) {
  auto current = node->right;
  node->right = current->left;
  current->left = node;
  node->height = std::max(getNodeHeight(node->left), getNodeHeight(node->right)) + 1;
  current->height = std::max(getNodeHeight(current->left), node->height) + 1;
  return current;
}

AVLNode *AVLTree::balanceNode(AVLNode *node) {
  if (!node) {
    return nullptr;
  }

  if (balanceFactor(node) > 1) {
    if (balanceFactor(node->left) >= 0) {
      return rotateRight(node);
    }
    node->left = rotateLeft(node->left);
    return rotateRight(node);
  }
  if (balanceFactor(node) < -1) {
    if (balanceFactor(node->right) <= 0) {
      return rotateLeft(node);
    }
    node->right = rotateRight(node->right);
    return rotateLeft(node);
  }

  return node;
}

AVLNode *AVLTree::insertNode(AVLNode *node, int value) {
  if (!node) {
    node = new AVLNode{value};
    ++size_;
    return node;
  }
  if (value == node->value) {
    return node;
  }

  if (value < node->value) {
    node->left = insertNode(node->left, value);
  } else {
    node->right = insertNode(node->right, value);
  }

  update(node);
  return balanceNode(node);
}

AVLNode *AVLTree::findMinNode(AVLNode *node) {
  if (node) {
    while (node->left) {
      node = node->left;
    }
  }
  return node;
}

AVLNode *AVLTree::removeMinNode(AVLNode *node) {
  if (!node) {
    return nullptr;
  }

  if (node->left) {
    node->left = removeMinNode(node->left);
  } else {
    if (node->right) {
      auto child = node->right;
      *node = *child;
      delete child;
    } else {
      delete node;
      node = nullptr;
    }
  }

  return node;
}

AVLNode *AVLTree::removeNode(AVLNode *node, int value) {
  if (!node) {
    return nullptr;
  }

  if (value < node->value) {
    node->left = removeNode(node->left, value);
  } else if (node->value < value) {
    node->right = removeNode(node->right, value);
  } else {
    --size_;
    if (node->left && node->right) {
      auto min_node = findMinNode(node->right);
      node->value = min_node->value;
      node->right = removeMinNode(node->right);
    } else if (!node->left && !node->right) {
      delete node;
      node = nullptr;
    } else {
      auto child = node->left ? node->left : node->right;
      *node = *child;
      delete child;
    }
  }

  if (!node) {
    return nullptr;
  }
  update(node);
  return balanceNode(node);
}

AVLNode *AVLTree::findNode(AVLNode *node, int value) {
  if (!node) {
    return nullptr;
  }

  if (node->value == value) {
    return node;
  }
  if (value < node->value) {
    return findNode(node->left, value);
  }
  return findNode(node->right, value);
}

void AVLTree::traversalInternal(AVLNode *node, int *array, int *index) {
  if (!node) {
    return;
  }

  traversalInternal(node->left, array, index);
  array[*index] = node->value;
  ++(*index);
  traversalInternal(node->right, array, index);
}

AVLNode *AVLTree::lowerBoundInternal(AVLNode *current, int value) const {
  if (!current) {
    return nullptr;
  }

  if (value < current->value) {
    auto new_node = lowerBoundInternal(current->left, value);
    if (!new_node) {
      return current;
    }
    return new_node;
  }
  if (current->value < value) {
    return lowerBoundInternal(current->right, value);
  }
  return current;
}

class Skiplist {
 public:
  Skiplist() : mt_((std::random_device())()) {
  }

  ~Skiplist() {
    Node *cur = head_.next[0];
    while (cur) {
      Node *next = cur->next[0];
      delete cur;
      cur = next;
    }
  }

  bool search(int target) {
    Node *cur = &head_;
    for (int i = levels_ - 1; i >= 0; --i) {
      for (; cur->next[i] != nullptr; cur = cur->next[i]) {
        if (cur->next[i]->value == target) {
          return true;
        }
        if (cur->next[i]->value > target) {
          break;
        }
      }
    }
    return false;
  }

  void add(int num) {
    int level = 1;
    while (Rand() > HALF && level < MAX_LEVEL) {
      ++level;
      if (level == levels_) {
        ++levels_;
        break;
      }
    }

    Node *new_node = new Node(level, num);
    Node *cur = &head_;
    for (int i = levels_ - 1; i >= 0; --i) {
      for (; cur->next[i] != nullptr; cur = cur->next[i]) {
        if (cur->next[i]->value > num) {
          break;
        }
      }
      if (i <= level) {
        new_node->next[i] = cur->next[i];
        cur->next[i] = new_node;
      }
    }
  }

  bool erase(int num) {
    Node *cur = &head_;
    bool found = false;
    for (int i = levels_ - 1; i >= 0; --i) {
      for (; cur->next[i] != nullptr; cur = cur->next[i]) {
        if (cur->next[i]->value == num) {
          found = true;
          cur->next[i] = cur->next[i]->next[i];
          break;
        }
        if (cur->next[i]->value > num) {
          break;
        }
      }
    }
    return found;
  }

 private:
  static constexpr int MAX_LEVEL = 50;
  static constexpr double HALF = 0.4;

  struct Node {
    std::vector<Node *> next{};
    int value{};

    Node(int level, int value) : next(level), value(value) {
    }
  };

  double Rand() {
    return distr_(mt_);
  }

  int levels_{1};
  Node head_{MAX_LEVEL, INT_MIN};
  std::mt19937_64 mt_{};
  std::uniform_real_distribution<double> distr_{0.0, 1.0};
};

void TestFunc() {
  constexpr int N = 100000;
  constexpr int SEARCH = 100;

  AVLTree tree;
  Skiplist skiplist;

  std::vector<int> to_search{};
  to_search.reserve(SEARCH);

  for (int i = 0; i < N; ++i) {
    int poor_random = rand();
    if (i % (N / SEARCH) == 0) {
      to_search.emplace_back(poor_random);
      std::cout << i << " added" << std::endl;
    }
    tree.insert(poor_random);
    skiplist.add(poor_random);
  }

  for (int i = 0; i < to_search.size(); ++i) {
    // find time for AVL
    auto start = std::chrono::high_resolution_clock::now();
    auto unused = tree.find(to_search[i]);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "AVL: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
    // std::cerr << *unused << ' ';

    // find time for Skiplist
    start = std::chrono::high_resolution_clock::now();
    skiplist.search(to_search[i]);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Skiplist: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << std::endl;
  }
}

void SkiplistFunc() {
  Skiplist skiplist;
  skiplist.add(1);
  skiplist.add(2);
  skiplist.add(3);
  std::cout << skiplist.search(0) << '\n';  // return False
  skiplist.add(4);
  std::cout << skiplist.search(1) << '\n';  // return True
  std::cout << skiplist.erase(0) << '\n';   // return False, 0 is not in skiplist.
  std::cout << skiplist.erase(1) << '\n';   // return True
  std::cout << skiplist.search(1) << '\n';  // return False, 1 has already been erased.
}

int main() {
  TestFunc();
  SkiplistFunc();
}
