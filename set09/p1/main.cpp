#include <cassert>
#include <compare>
#include <iostream>
#include <queue>
#include <random>
#include <string>
#include <utility>
#include <vector>

using namespace std::string_literals;

std::vector<std::string> table(26);

struct Node {
  char value = 0;
  int count = 0;
  Node* left = nullptr;
  Node* right = nullptr;
  Node(char value, int count, Node* left = nullptr, Node* right = nullptr)
      : value(value), count(count), left(left), right(right) {
  }
};

// Custom comparator for priority_queue (min-heap by count)
struct NodePtrCmp {
  bool operator()(const Node* lhs, const Node* rhs) const {
    return lhs->count > rhs->count;
  }
};

Node* BuildTrie(const std::vector<int>& freq) {
  std::priority_queue<Node*, std::vector<Node*>, NodePtrCmp> pq;
  for (size_t i = 0; i < freq.size(); ++i) {
    if (freq[i] > 0) {
      pq.push(new Node(static_cast<char>(i + 'a'), freq[i]));
    }
  }

  while (pq.size() > 1) {
    Node* left = pq.top();
    pq.pop();
    Node* right = pq.top();
    pq.pop();
    Node* parent = new Node(0, left->count + right->count, left, right);
    pq.push(parent);
  }

  return pq.top();
}

void ToTable(Node* node, const std::string& code) {
  if (node->left == nullptr && node->right == nullptr) {
    table[node->value - 'a'] = std::max(code, "0"s);
    return;
  }
  if (node->left) {
    ToTable(node->left, code + "0");
  }
  if (node->right) {
    ToTable(node->right, code + "1");
  }
}

int main() {
  std::string input;
  std::cin >> input;
  std::vector<int> freq(26, 0);
  int count_node = 0;
  for (char c : input) {
    if (freq[c - 'a'] == 0) {
      ++count_node;
    }
    ++freq[c - 'a'];
  }

  Node* root = BuildTrie(freq);
  ToTable(root, "");
  std::string encoded;
  encoded.reserve(input.size() * 5);
  for (char c : input) {
    encoded += table[c - 'a'];
  }
  std::cout << count_node << ' ' << encoded.size() << '\n';
  for (size_t i = 0; i < table.size(); ++i) {
    if (freq[i] > 0) {
      std::cout << static_cast<char>(i + 'a') << ": " << table[i] << '\n';
    }
  }
  std::cout << encoded << '\n';
}