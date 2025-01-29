#include <algorithm>
#include <iostream>
#include <random>

std::mt19937 rnd{52};

struct Node {
  int height;
  int size;
  Node *left;
  Node *right;
  int value;

  Node(int value);

  ~Node();
};

class RandTree {
 public:
  RandTree();
  explicit RandTree(int value);

  int getHeight();
  void insert(int value);
  void erase(int value);
  int *find(int value);
  int *traversal();
  int *lowerBound(int value);
  bool empty();
  Node *getRoot();
  int getSize();
  ~RandTree();

 private:
  Node *root_;

  int getNodeSize(Node *node);
  int getNodeHeight(Node *node);
  void update(Node *node);
  Node *rotateRight(Node *node);
  Node *rotateLeft(Node *node);
  Node *insertNode(Node *node, int value);
  Node *insertRoot(Node *node, int value);
  Node *findMinNode(Node *node);
  Node *treeJoin(Node *p, Node *q);
  Node *removeNode(Node *node, int value);
  Node *findNode(Node *node, int value);
  void traversalInternal(Node *node, int *array, int *index);
  Node *lowerBoundInternal(Node *current, int value) const;
};

Node::Node(int value) : height{0}, left{nullptr}, right{nullptr}, value{value}, size{1} {
}

Node::~Node() = default;

RandTree::RandTree() : root_{nullptr} {
}

RandTree::RandTree(int value) {
  root_ = new Node{value};
}

int RandTree::getHeight() {
  return getNodeHeight(root_) + 1;
}

void RandTree::insert(int value) {
  auto node = findNode(root_, value);
  if (node) {
    return;
  }
  root_ = insertNode(root_, value);
}

void RandTree::erase(int value) {
  root_ = removeNode(root_, value);
}

int *RandTree::find(int value) {
  auto node = findNode(root_, value);
  if (!node) {
    return nullptr;
  }
  return &node->value;
}

int *RandTree::traversal() {
  int *array = new int[root_->size];
  int *index = new int;
  *index = 0;

  traversalInternal(root_, array, index);
  return array;
}

int *RandTree::lowerBound(int value) {
  auto node = lowerBoundInternal(root_, value);
  if (!node) {
    return nullptr;
  }
  return &node->value;
}

bool RandTree::empty() {
  return getNodeSize(root_) == 0;
}

Node *RandTree::getRoot() {
  return root_;
}

int RandTree::getSize() {
  return getNodeSize(root_);
}

void clear(Node *&node) {
  if (node) {
    clear(node->left);
    clear(node->right);
    delete node;
    node = nullptr;
  }
}

RandTree::~RandTree() {
  clear(root_);
}

int RandTree::getNodeSize(Node *node) {
  if (!node) {
    return 0;
  }
  return node->size;
}

int RandTree::getNodeHeight(Node *node) {
  if (!node) {
    return -1;
  }
  return node->height;
}

void RandTree::update(Node *node) {
  if (!node) {
    return;
  }
  node->height = std::max(getNodeHeight(node->left), getNodeHeight(node->right)) + 1;
  node->size = getNodeSize(node->left) + getNodeSize(node->right) + 1;
}

Node *RandTree::rotateRight(Node *node) {
  auto current = node->left;
  node->left = current->right;
  current->right = node;
  update(node);
  update(current);
  return current;
}

Node *RandTree::rotateLeft(Node *node) {
  auto current = node->right;
  node->right = current->left;
  current->left = node;
  update(node);
  update(current);
  return current;
}

Node *RandTree::insertNode(Node *node, int value) {
  if (!node) {
    return new Node{value};
  }

  if (rnd() % (getNodeSize(node) + 1) == 0) {
    return insertRoot(node, value);
  }

  if (value < node->value) {
    node->left = insertNode(node->left, value);
  } else {
    node->right = insertNode(node->right, value);
  }

  update(node);
  return node;
}

Node *RandTree::insertRoot(Node *node, int value) {
  if (!node) {
    return new Node{value};
  }

  if (value < node->value) {
    node->left = insertRoot(node->left, value);
    return rotateRight(node);
  }
  node->right = insertRoot(node->right, value);
  return rotateLeft(node);
}

Node *RandTree::findMinNode(Node *node) {
  if (node) {
    while (node->left) {
      node = node->left;
    }
  }
  return node;
}

Node *RandTree::treeJoin(Node *p, Node *q) {
  if (!p) {
    return q;
  }
  if (!q) {
    return p;
  }

  if (rnd() % (getNodeSize(p) + getNodeSize(q)) < getNodeSize(p)) {
    p->right = treeJoin(p->right, q);
    update(p);
    return p;
  }
  q->left = treeJoin(p, q->left);
  update(q);
  return q;
}

Node *RandTree::removeNode(Node *node, int value) {
  if (!node) {
    return nullptr;
  }

  if (value < node->value) {
    node->left = removeNode(node->left, value);
  } else if (node->value < value) {
    node->right = removeNode(node->right, value);
  } else {
    node = treeJoin(node->left, node->right);
  }

  update(node);
  return node;
}

Node *RandTree::findNode(Node *node, int value) {
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

void RandTree::traversalInternal(Node *node, int *array, int *index) {
  if (!node) {
    return;
  }

  traversalInternal(node->left, array, index);
  array[*index] = node->value;
  ++(*index);
  traversalInternal(node->right, array, index);
}

Node *RandTree::lowerBoundInternal(Node *current, int value) const {
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

int main() {
  RandTree tree{};
  for (int i = 0; i < 10; ++i) {
    tree.insert(i);
  }

  tree.erase(5);

  auto traverse = tree.traversal();
  for (int i = 0; i < 9; ++i) {
    std::cout << traverse[i];
  }

  tree.insert(15);
  traverse = tree.traversal();
  for (int i = 0; i < 9; ++i) {
    std::cout << traverse[i];
  }
  return 0;
}