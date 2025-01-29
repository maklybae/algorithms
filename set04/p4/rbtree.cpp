#include "rbtree.h"

#include <algorithm>

// todo: fix height
Node::Node(int key)
    : key{key}, height{-10000000}, size{1}, left{nullptr}, right{nullptr}, parent{nullptr}, color{Color::RED} {
}

RBTree::RBTree() : root{nullptr} {
}

RBTree::RBTree(std::initializer_list<int> list) : root{nullptr} {
  for (int key : list) {
    insert(key);
  }
}

void Clear(Node *&node) {
  if (node) {
    Clear(node->left);
    Clear(node->right);
    delete node;
    node = nullptr;
  }
}

RBTree::~RBTree() {
  Clear(root);
}

static Node *FindNode(Node *node, int value) {
  if (!node) {
    return nullptr;
  }

  if (node->key == value) {
    return node;
  }
  if (value < node->key) {
    return FindNode(node->left, value);
  }
  return FindNode(node->right, value);
}

int *RBTree::find(int key) {
  auto node = FindNode(root, key);
  if (!node) {
    return nullptr;
  }
  return &node->key;
}

int RBTree::size() const {
  if (!root) {
    return 0;
  }
  return root->size;
}

static Node *LowerBoundInternal(Node *current, int value) {
  if (!current) {
    return nullptr;
  }

  if (value < current->key) {
    auto new_node = LowerBoundInternal(current->left, value);
    if (!new_node) {
      return current;
    }
    return new_node;
  }
  if (current->key < value) {
    return LowerBoundInternal(current->right, value);
  }
  return current;
}

int *RBTree::lowerBound(int key) {
  auto node = LowerBoundInternal(root, key);
  if (!node) {
    return nullptr;
  }
  return &node->key;
}

bool RBTree::empty() const {
  return !root;
}

static int GetNodeSize(Node *node) {
  if (!node) {
    return 0;
  }
  return node->size;
}

static int GetNodeHeight(Node *node) {
  if (!node) {
    return 0;
  }
  return node->height;
}

static Color GetNodeColor(Node *node) {
  if (!node) {
    return Color::BLACK;
  }
  return node->color;
}

static void RotateRight(Node *node, Node *&root) {
  auto current = node->left;
  node->left = current->right;
  if (current->right) {
    current->right->parent = node;
  }
  current->parent = node->parent;
  if (!node->parent) {
    root = current;
  } else if (node == node->parent->left) {
    node->parent->left = current;
  } else {
    node->parent->right = current;
  }
  current->right = node;
  node->parent = current;

  // Update heights
  // node->height = std::max(GetNodeHeight(node->left) + (GetNodeColor(node->left) == Color::BLACK),
  // GetNodeHeight(node->right) + (GetNodeColor(node->right) == Color::BLACK));
  node->size = GetNodeSize(node->left) + GetNodeSize(node->right) + 1;
  // current->height = std::max(GetNodeHeight(current->left) + (GetNodeColor(current->left) ==
  // Color::BLACK),
  //  GetNodeHeight(current->right) + (GetNodeColor(current->right) == Color::BLACK));
  current->size = GetNodeSize(current->left) + GetNodeSize(current->right) + 1;
}

static void RotateLeft(Node *node, Node *&root) {
  auto current = node->right;
  node->right = current->left;
  if (current->left) {
    current->left->parent = node;
  }
  current->parent = node->parent;
  if (!node->parent) {
    root = current;
  } else if (node == node->parent->left) {
    node->parent->left = current;
  } else {
    node->parent->right = current;
  }
  current->left = node;
  node->parent = current;

  // Update heights
  // node->height = std::max(GetNodeHeight(node->left) + (GetNodeColor(node->left) == Color::BLACK),
  // GetNodeHeight(node->right) + (GetNodeColor(node->right) == Color::BLACK));
  node->size = GetNodeSize(node->left) + GetNodeSize(node->right) + 1;
  // current->height = std::max(GetNodeHeight(current->left) + (GetNodeColor(current->left) == Color::BLACK),
  //  GetNodeHeight(current->right) + (GetNodeColor(current->right) == Color::BLACK));
  current->size = GetNodeSize(current->left) + GetNodeSize(current->right) + 1;
}

static Node *InsertNode(Node *node, int value) {
  if (!node) {
    node = new Node{value};
    return node;
  }
  if (value == node->key) {
    return node;
  }

  ++node->size;
  if (value < node->key) {
    node->left = InsertNode(node->left, value);
    node->left->parent = node;
  } else {
    node->right = InsertNode(node->right, value);
    node->right->parent = node;
  }
  // node->height = std::max(GetNodeHeight(node->left) + (GetNodeColor(node->left) == Color::BLACK),
  // GetNodeHeight(node->right) + (GetNodeColor(node->right) == Color::BLACK));

  return node;
}

static void FixInsertNode(Node *&root, int value) {
  auto node = FindNode(root, value);

  while (GetNodeColor(node->parent) == Color::RED) {
    if (node->parent == node->parent->parent->left) {
      auto uncle = node->parent->parent->right;

      if (GetNodeColor(uncle) == Color::RED) {
        node->parent->color = Color::BLACK;
        uncle->color = Color::BLACK;
        node->parent->parent->color = Color::RED;
        // ++node->parent->parent->height;  // may be
        node = node->parent->parent;
      } else {
        if (node == node->parent->right) {
          node = node->parent;
          RotateLeft(node, root);
        }
        node->parent->color = Color::BLACK;
        node->parent->parent->color = Color::RED;
        RotateRight(node->parent->parent, root);
      }
    } else {
      auto uncle = node->parent->parent->left;

      if (GetNodeColor(uncle) == Color::RED) {
        node->parent->color = Color::BLACK;
        uncle->color = Color::BLACK;
        node->parent->parent->color = Color::RED;
        // ++node->parent->parent->height;  // may be
        node = node->parent->parent;
      } else {
        if (node == node->parent->left) {
          node = node->parent;
          RotateRight(node, root);
        }
        node->parent->color = Color::BLACK;
        node->parent->parent->color = Color::RED;
        RotateLeft(node->parent->parent, root);
      }
    }
  }

  root->color = Color::BLACK;
}

void RBTree::insert(int key) {
  if (find(key)) {
    return;
  }
  root = InsertNode(root, key);
  FixInsertNode(root, key);
}