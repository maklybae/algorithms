#include "avl_tree.h"

#include <algorithm>

Node::Node(int value) : height{0}, left{nullptr}, right{nullptr}, value{value} {
}

Node::~Node() = default;

RandTree::RandTree() : root_{nullptr}, size_{0} {
}

RandTree::RandTree(int value) {
  root_ = new Node{value};
  size_ = 1;
}

int RandTree::getHeight() {
  return getNodeHeight(root_) + 1;
}

void RandTree::insert(int value) {
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
  int *array = new int[size_];
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
  return size_ == 0;
}

Node *RandTree::getRoot() {
  return root_;
}

int RandTree::getSize() {
  return size_;
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

int RandTree::getNodeHeight(Node *node) {
  if (!node) {
    return -1;
  }
  return node->height;
}

int RandTree::balanceFactor(Node *node) {
  return getNodeHeight(node->left) - getNodeHeight(node->right);
}

void RandTree::update(Node *node) {  // ???? что этот метод должен делать ????
  if (!node) {
    return;
  }
  node->height = std::max(getNodeHeight(node->left), getNodeHeight(node->right)) + 1;
}

Node *RandTree::rotateRight(Node *node) {
  auto current = node->left;
  node->left = current->right;
  current->right = node;
  node->height = std::max(getNodeHeight(node->left), getNodeHeight(node->right)) + 1;
  current->height = std::max(getNodeHeight(current->left), node->height) + 1;
  return current;
}

Node *RandTree::rotateLeft(Node *node) {
  auto current = node->right;
  node->right = current->left;
  current->left = node;
  node->height = std::max(getNodeHeight(node->left), getNodeHeight(node->right)) + 1;
  current->height = std::max(getNodeHeight(current->left), node->height) + 1;
  return current;
}

Node *RandTree::balanceNode(Node *node) {
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

Node *RandTree::insertNode(Node *node, int value) {
  if (!node) {
    node = new Node{value};
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

Node *RandTree::findMinNode(Node *node) {
  if (node) {
    while (node->left) {
      node = node->left;
    }
  }
  return node;
}

Node *RandTree::removeMinNode(Node *node) {
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

Node *RandTree::removeNode(Node *node, int value) {
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
