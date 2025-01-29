#include <algorithm>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

std::mt19937 rnd{52};

struct Node {
  int key;
  uint64_t prior;
  int size = 1;
  int64_t sum;
  Node *left = nullptr;
  Node *right = nullptr;

  explicit Node(int key) : key{key}, prior{rnd()}, sum{key} {
  }
};

using SplitPair = std::pair<Node *, Node *>;

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

static int64_t GetSum(Node *node) {
  if (!node) {
    return 0;
  }
  return node->sum;
}

static void Update(Node *node) {
  if (!node) {
    return;
  }
  node->size = GetSize(node->left) + GetSize(node->right) + 1;
  node->sum = GetSum(node->left) + GetSum(node->right) + node->key;
}

static SplitPair Split(Node *node, int k) {
  if (!node) {
    return {nullptr, nullptr};
  }

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
    left->right = Merge(left->right, right);
    Update(left);
    return left;
  }
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

  // int mn = GetMin(right_split.first);
  // node = Merge(left_split.first, Merge(right_split.first, right_split.second));
  // return mn;
}

static void Swap(Node *&even, Node *&odd, int left, int right) {
  int even_left = (left + 1) / 2;
  int even_right = (right + 1) / 2;
  // [0, left) [left, n)
  SplitPair even_left_split = Split(even, even_left);
  // [left, right) [right, n)
  SplitPair even_right_split = Split(even_left_split.second, even_right - even_left);

  int odd_left = left / 2;
  int odd_right = right / 2;
  // [0, left) [left, n)
  SplitPair odd_left_split = Split(odd, odd_left);
  // [left, right) [right, n)
  SplitPair odd_right_split = Split(odd_left_split.second, odd_right - odd_left);

  even = Merge(even_left_split.first, Merge(odd_right_split.first, even_right_split.second));
  odd = Merge(odd_left_split.first, Merge(even_right_split.first, odd_right_split.second));
}

static int64_t Sum(Node *&even, Node *&odd, int left, int right) {
  int even_left = (left + 1) / 2;
  int even_right = (right + 1) / 2;
  // [0, left) [left, n)
  SplitPair even_left_split = Split(even, even_left);
  // [left, right) [right, n)
  SplitPair even_right_split = Split(even_left_split.second, even_right - even_left);

  int odd_left = left / 2;
  int odd_right = right / 2;
  // [0, left) [left, n)
  SplitPair odd_left_split = Split(odd, odd_left);
  // [left, right) [right, n)
  SplitPair odd_right_split = Split(odd_left_split.second, odd_right - odd_left);

  int64_t ans{GetSum(even_right_split.first) + GetSum(odd_right_split.first)};
  even = Merge(even_left_split.first, Merge(even_right_split.first, even_right_split.second));
  odd = Merge(odd_left_split.first, Merge(odd_right_split.first, odd_right_split.second));
  return ans;
}

int main() {
  int counter = 0;
  int n{};
  int m{};
  std::cin >> n >> m;

  while (!(n == 0 && m == 0)) {
    Node *even{};
    Node *odd{};

    for (int i = 0; i < n; ++i) {
      int tmp{};
      std::cin >> tmp;
      if (i % 2 == 0) {
        even = Insert(even, tmp);
      } else {
        odd = Insert(odd, tmp);
      }
    }

    std::cout << "Swapper " << ++counter << ":\n";
    for (int i = 0; i < m; ++i) {
      int req{};
      int a{};
      int b{};
      std::cin >> req >> a >> b;
      --a;

      if (req == 1) {
        Swap(even, odd, a, b);
      } else {
        std::cout << Sum(even, odd, a, b) << '\n';
      }
    }
    std::cout << '\n';

    std::cin >> n >> m;
  }
}