#include <iostream>
#include <vector>

struct BinaryNode {
  int key;
  int left;
  int right;
  char color;
};

std::vector<BinaryNode> storage;

bool CheckRB(int number, int cur_bh, int bh) {
  if (number == 0) {
    return cur_bh == bh;
  }

  BinaryNode& cur = storage[number];
  if (cur.color == 'B') {
    ++cur_bh;
  }
  return (!cur.left || storage[cur.left].key < cur.key) && (!cur.right || cur.key < storage[cur.right].key) &&
         (cur.color != 'R' || storage[cur.left].color == 'B') &&
         (cur.color != 'R' || storage[cur.right].color == 'B') && CheckRB(cur.left, cur_bh, bh) &&
         CheckRB(cur.right, cur_bh, bh);
}

bool CheckRB(int root) {
  if (storage[root].color != 'B') {
    return false;
  }

  int bh{};
  int cur{root};

  while (cur != 0) {
    if (storage[cur].color == 'B') {
      ++bh;
    }
    cur = storage[cur].left;
  }

  CheckRB(root, 0, bh);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n{};
  int root{};
  std::cin >> n >> root;
  if (n == 0) {
    std::cout << "NO\n";
    return 0;
  }

  storage = std::vector<BinaryNode>(n + 1);
  storage[0].color = 'B';

  for (int i = 0; i < n; ++i) {
    int number{};
    int key{};
    std::string s_left{};
    std::string s_right{};
    char color{};
    std::cin >> number >> key >> s_left >> s_right >> color;

    storage[number].key = key;
    storage[number].color = color;
    if (s_left != "null") {
      storage[number].left = std::stoi(s_left);
    } else {
      storage[number].left = 0;
    }
    if (s_right != "null") {
      storage[number].right = std::stoi(s_right);
    } else {
      storage[number].right = 0;
    }
  }

  if (CheckRB(root)) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }
}