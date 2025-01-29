#include <algorithm>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

std::mt19937 rnd{52};

class ImplicitTreap {
 public:
  ImplicitTreap() = default;
  ~ImplicitTreap() {
    Clear(root_);
  }

  void Insert(int key) {
    root_ = Insert(root_, key);
  }

  void Erase(int key) {

  }

  std::vector<int> Traverse() const {
    std::vector<int> array{};
    array.reserve(GetSize(root_));
    Traverse(root_, array);
    return array;
  }

  int Min(int left, int right) {
    return Min(root_, left, right);
  }

  int Max(int left, int right) {
    return Max(root_, left, right);
  }

  void Add(int left, int right, int d) {
    Add(root_, left, right, d);
  }

 private:
  struct Node {
    int key;
    uint prior;
    int size = 1;
    int min;
    int max;
    int promise = 0;
    Node *left = nullptr;
    Node *right = nullptr;

    explicit Node(int key) : key{key}, prior{rnd()}, min{key}, max{key} {
    }
  };

  using SplitPair = std::pair<Node *, Node *>;

  Node *root_ = nullptr;

  static void Clear(Node *node) {
    if (node) {
      Clear(node->left);
      Clear(node->right);
      delete node;
      node = nullptr;
    }
  }

  static int GetSize(Node *node) {
    if (!node) {
      return 0;
    }
    return node->size;
  }

  static int GetMin(Node *node) {
    if (!node) {
      return INT_MAX;
    }
    return node->min;
  }

  static int GetMax(Node *node) {
    if (!node) {
      return INT_MIN;
    }
    return node->max;
  }

  static void Update(Node *node) {
    if (!node) {
      return;
    }
    node->size = GetSize(node->left) + GetSize(node->right) + 1;
    node->min = std::min(std::min(GetMin(node->left), GetMin(node->right)), node->key);
    node->max = std::max(std::max(GetMax(node->left), GetMax(node->right)), node->key);
  }

  static void ApplyAdd(Node *node, int d) {
    if (!node) {
      return;
    }
    node->promise += d;
    node->min += d;
    node->max += d;
    node->key += d;
  }

  static void Push(Node *node) {
    if (!node || node->promise == 0) {
      return;
    }

    ApplyAdd(node->left, node->promise);
    ApplyAdd(node->right, node->promise);
    node->promise = 0;
  }

  static SplitPair Split(Node *node, int k) {
    if (!node) {
      return {nullptr, nullptr};
    }

    Push(node);
    if (GetSize(node->left) + 1 <= k) {
      SplitPair right_split = Split(node->right, k - GetSize(node->left) - 1);
      node->right = right_split.first;
      Update(node);
      return {node, right_split.second};
    }
    SplitPair left_split = Split(node->left, k);
    node->left = left_split.second;
    Update(node);
    return {left_split.first, node};
  }

  static Node *Merge(Node *left, Node *right) {
    if (!left) {
      return right;
    }
    if (!right) {
      return left;
    }

    if (left->prior > right->prior) {
      Push(left);
      left->right = Merge(left->right, right);
      Update(left);
      return left;
    }
    Push(right);
    right->left = Merge(left, right->left);
    Update(right);
    return right;
  }

  static Node *Insert(Node *node, int key) {
    Node *new_node = new Node{key};
    return Merge(node, new_node);
  }

  static int Min(Node *&node, int left, int right) {
    // [0, left) [left, n)
    SplitPair left_split = Split(node, left);
    // [left, right) [right, n)
    SplitPair right_split = Split(left_split.second, right - left);

    int mn = GetMin(right_split.first);
    node = Merge(left_split.first, Merge(right_split.first, right_split.second));
    return mn;
  }

  static int Max(Node *&node, int left, int right) {
    // [0, left) [left, n)
    SplitPair left_split = Split(node, left);
    // [left, right) [right, n)
    SplitPair right_split = Split(left_split.second, right - left);

    int mx = GetMax(right_split.first);
    node = Merge(left_split.first, Merge(right_split.first, right_split.second));
    return mx;
  }

  static void Add(Node *&node, int left, int right, int d) {
    // [0, left) [left, n)
    SplitPair left_split = Split(node, left);
    // [left, right) [right, n)
    SplitPair right_split = Split(left_split.second, right - left);

    ApplyAdd(right_split.first, d);
    node = Merge(left_split.first, Merge(right_split.first, right_split.second));
  }

  static void Traverse(Node *node, std::vector<int> &array) {
    if (!node) {
      return;
    }

    Push(node);
    Traverse(node->left, array);
    array.push_back(node->key);
    Traverse(node->right, array);
  }
};

int main() {
  std::vector<int> input{};
  input.reserve(15);
  for (int i = 0; i < 15; ++i) {
    input.push_back(rnd() % 100);
    std::cout << input.back() << ' ';
  }
  std::cout << '\n';

  ImplicitTreap treap{};
  for (int i = 0; i < 15; ++i) {
    treap.Insert(input[i]);
  }

  auto input_treap = treap.Traverse();
  for (int i = 0; i < 15; ++i) {
    std::cout << input_treap[i] << ' ';
  }
  std::cout << '\n';

  std::cout << "Min all: " << treap.Min(0, 15) << '\n';
  std::cout << "Max all: " << treap.Max(0, 15) << '\n';
  std::cout << "Min [2, 4): " << treap.Min(2, 4) << '\n';
  std::cout << "Max [2, 5): " << treap.Max(2, 5) << '\n';
  std::cout << "Min [5, 10): " << treap.Min(5, 10) << '\n';
  std::cout << "Max [5, 10): " << treap.Max(5, 10) << '\n';

  treap.Add(2, 5, 1);
  auto add_traverse = treap.Traverse();
  for (int i = 0; i < 15; ++i) {
    std::cout << add_traverse[i] << ' ';
  }
  std::cout << '\n';

  std::cout << "Min all: " << treap.Min(0, 15) << '\n';
  std::cout << "Max all: " << treap.Max(0, 15) << '\n';
  std::cout << "Min [2, 5): " << treap.Min(2, 5) << '\n';
  std::cout << "Max [2, 5): " << treap.Max(2, 5) << '\n';
  std::cout << "Min [5, 10): " << treap.Min(5, 10) << '\n';
  std::cout << "Max [5, 10): " << treap.Max(5, 10) << '\n';

  treap.Erase(44);
  add_traverse = treap.Traverse();
  for (int i = 0; i < 15; ++i) {
    std::cout << add_traverse[i] << ' ';
  }
  std::cout << '\n';
}