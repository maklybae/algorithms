struct Node {
  Node(int key, Node *parent);

  int key;
  Node *left;
  Node *right;
  Node *parent;
};

class SplayTree {
 public:
  SplayTree();

  ~SplayTree();

  void insert(int);

  Node *find(int) const;

  int splay(Node *);

  int getHeight() const;

 private:
  Node *root;

  void clear(Node *node);

  void rotateLeft(Node *node);

  void rotateRight(Node *node);

  // inner implementation of public getHeight() method
  int getHeight(Node *node) const;
};