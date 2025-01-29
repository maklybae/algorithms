#include "btree.h"

Node::Node(int t) : t{t}, key{}, children{}, parent{nullptr}, isLeaf{true} {
  key.reserve(2 * t - 1);
  children.reserve(2 * t);
}

static void ClearNode(Node* node) {
  if (node == nullptr) {
    return;
  }
  for (size_t i = 0; i < node->children.size(); ++i) {
    ClearNode(node->children[i]);
  }
  delete node;
}

BTree::~BTree() {
  ClearNode(root);
}

BTree::BTree(int t) : t_{t}, size_{0}, root{nullptr} {
}

void SplitChild(Node* parent, size_t ind) {
  Node* node = parent->children[ind];
  Node* new_node = new Node{parent->t};
  new_node->isLeaf = node->isLeaf;
  new_node->parent = node->parent;

  for (size_t i = node->t; i < 2 * node->t - 1; ++i) {
    new_node->key.push_back(node->key[i]);
  }
  int median = node->key[node->t - 1];
  node->key.erase(node->key.begin() + (node->t - 1), node->key.end());

  if (!node->isLeaf) {
    for (size_t i = node->t; i < 2 * node->t; ++i) {
      new_node->children.push_back(node->children[i]);
    }
    node->children.erase(node->children.begin() + node->t, node->children.end());
  }

  parent->key.insert(parent->key.begin() + ind, median);
  parent->children.insert(parent->children.begin() + ind + 1, new_node);
}

void InsertNonfull(Node* node, int key, int& size) {
  size_t i = 0;
  while (i < node->key.size() && node->key[i] < key) {
    ++i;
  }

  if (node->isLeaf) {
    node->key.insert(node->key.begin() + i, key);
  } else {
    auto to_insert = node->children[i];
    if (to_insert->key.size() == 2 * to_insert->t - 1) {
      SplitChild(node, i);
      ++size;
      if (key > node->key[i]) {
        to_insert = node->children[i + 1];
      }
    }
    InsertNonfull(to_insert, key, size);
  }
}

Node* FindNode(Node* node, int key) {
  if (!node) {
    return nullptr;
  }

  size_t i = 0;
  while (i < node->key.size() && node->key[i] < key) {
    ++i;
  }
  if (i < node->key.size() && node->key[i] == key) {
    return node;
  }
  if (node->isLeaf) {
    return nullptr;
  }
  return FindNode(node->children[i], key);
}

void BTree::insert(int key) {
  if (!root) {
    root = new Node{t_};
    ++size_;
    root->key.push_back(key);
    return;
  }
  if (FindNode(root, key)) {
    return;
  }

  if (root->key.size() == 2 * root->t - 1) {
    auto new_root = new Node{t_};
    new_root->isLeaf = false;
    new_root->children.push_back(root);
    root->parent = new_root;
    ++size_;

    SplitChild(new_root, 0);
    ++size_;
    root = new_root;
  }
  InsertNonfull(root, key, size_);
}

size_t BTree::size() const {
  return size_;
}

int64_t SumLeafs(Node* node) {
  if (!node) {
    return 0;
  }
  int64_t sum{};
  if (node->isLeaf) {
    for (size_t i = 0; i < node->key.size(); ++i) {
      sum += node->key[i];
    }
  } else {
    for (size_t i = 0; i < node->children.size(); ++i) {
      sum += SumLeafs(node->children[i]);
    }
  }
  return sum;
}

int64_t BTree::sum() const {
  if (!root) {
    return 0;
  }
  return SumLeafs(root);
}