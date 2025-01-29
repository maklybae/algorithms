#include <algorithm>

#include "splay-tree.h"

Node::Node(int key, Node *parent) : key{key}, parent{parent}, left{nullptr}, right{nullptr} {
}

SplayTree::SplayTree() : root{nullptr} {
}

SplayTree::~SplayTree() {
  clear(root);
}

void SplayTree::clear(Node *node) {
  if (node) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}

void SplayTree::rotateLeft(Node *node) {
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
}

void SplayTree::rotateRight(Node *node) {
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
}

int SplayTree::getHeight() const {
  return getHeight(root);
}

int SplayTree::getHeight(Node *node) const {
  if (!node) {
    return -1;
  }

  return std::max(getHeight(node->left), getHeight(node->right)) + 1;
}

static Node *FindNode(Node *node, int key) {
  if (!node) {
    return nullptr;
  }

  if (key < node->key) {
    return FindNode(node->left, key);
  }
  if (node->key < key) {
    return FindNode(node->right, key);
  }
  return node;
}

Node *SplayTree::find(int key) const {
  return FindNode(root, key);
}

static Node *InsertNode(Node *node, Node *parent, int key) {
  if (!node) {
    node = new Node{key, parent};
    return node;
  }

  if (key < node->key) {
    node->left = InsertNode(node->left, node, key);
  } else if (node->key < key) {
    node->right = InsertNode(node->right, node, key);
  }

  return node;
}

void SplayTree::insert(int key) {
  root = InsertNode(root, nullptr, key);
}

int SplayTree::splay(Node *node) {
  if (node == nullptr) {
    return 0;
  }

  int counter = 0;
  while (node != root) {
    if (node->parent == root) {
      ++counter;
      if (node == node->parent->left) {
        rotateRight(node->parent);
      } else {
        rotateLeft(node->parent);
      }
    } else if (node == node->parent->left && node->parent == node->parent->parent->left) {
      counter += 2;
      rotateRight(node->parent->parent);
      rotateRight(node->parent);
    } else if (node == node->parent->right && node->parent == node->parent->parent->right) {
      counter += 2;
      rotateLeft(node->parent->parent);
      rotateLeft(node->parent);
    } else if (node == node->parent->right && node->parent == node->parent->parent->left) {
      ++counter;
      rotateLeft(node->parent);
      rotateRight(node->parent);
    } else if (node == node->parent->left && node->parent == node->parent->parent->right) {
      ++counter;
      rotateRight(node->parent);
      rotateLeft(node->parent);
    }
  }

  return counter;
}