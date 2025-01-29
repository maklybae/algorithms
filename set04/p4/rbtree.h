#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <initializer_list>

enum class Color { RED, BLACK };

struct Node {
  int key;
  int height;
  int size;
  Node *left;
  Node *right;
  Node *parent;
  Color color;

  explicit Node(int key);
};

class RBTree {
 public:
  RBTree();

  RBTree(std::initializer_list<int> list);

  ~RBTree();

  void insert(int key);

  int *find(int key);

  int size() const;

  int *lowerBound(int key);

  bool empty() const;

  Node *root = nullptr;
};

#endif
