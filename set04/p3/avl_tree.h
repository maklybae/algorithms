#ifndef TEMPLATE_H
#define TEMPLATE_H

struct Node {
  int height;
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
  int size_;

  int getNodeHeight(Node *node);

  int balanceFactor(Node *node);

  void update(Node *node);

  Node *rotateRight(Node *node);

  Node *rotateLeft(Node *node);

  Node *balanceNode(Node *node);

  Node *insertNode(Node *node, int value);

  Node *findMinNode(Node *node);

  Node *removeMinNode(Node *node);

  Node *removeNode(Node *node, int value);

  Node *findNode(Node *node, int value);

  void traversalInternal(Node *node, int *array, int *index);

  Node *lowerBoundInternal(Node *current, int value) const;
};

#endif
