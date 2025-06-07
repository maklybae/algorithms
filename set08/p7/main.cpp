#include <cassert>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

struct trie_node {
  std::map<char, trie_node*> child;
  trie_node* suffix_link;
  trie_node* output_link;
  std::vector<int> pattern_inds;
};

trie_node* add_node() {
  trie_node* temp = new trie_node;
  temp->suffix_link = nullptr;
  temp->output_link = nullptr;
  return temp;
}

void build_Trie(trie_node* root, std::vector<std::string>& patterns) {
  for (size_t i = 0; i < patterns.size(); ++i) {
    trie_node* cur = root;
    for (auto c : patterns[i]) {
      if (cur->child.count(c)) {
        cur = cur->child[c];
      } else {
        trie_node* new_child = add_node();
        cur->child.insert({c, new_child});
        cur = new_child;
      }
    }
    cur->pattern_inds.push_back(i);
  }
}

void build_suffix_and_output_links(trie_node* root) {
  root->suffix_link = root;
  std::queue<trie_node*> qu;
  for (auto& it : root->child) {
    qu.push(it.second);
    it.second->suffix_link = root;
  }
  while (qu.size()) {
    trie_node* cur_state = qu.front();
    qu.pop();
    for (auto& it : cur_state->child) {
      char c = it.first;
      trie_node* temp = cur_state->suffix_link;
      while (temp->child.count(c) == 0 && temp != root) {
        temp = temp->suffix_link;
      }
      if (temp->child.count(c)) {
        it.second->suffix_link = temp->child[c];
      } else {
        it.second->suffix_link = root;
      }
      qu.push(it.second);
    }
    if (!cur_state->suffix_link->pattern_inds.empty()) {
      cur_state->output_link = cur_state->suffix_link;
    } else {
      cur_state->output_link = cur_state->suffix_link->output_link;
    }
  }
}

void search_pattern(trie_node* root, std::string& text, auto& indices, std::vector<std::string>& patterns) {
  trie_node* parent = root;
  for (size_t i = 0; i < text.length(); ++i) {
    char c = text[i];
    if (parent->child.count(c)) {
      parent = parent->child[c];
      trie_node* temp = parent;
      while (temp != nullptr) {
        for (int ind : temp->pattern_inds) {
          indices[ind].push_back(i);
        }
        temp = temp->output_link;
      }
    } else {
      while (parent != root && parent->child.count(c) == 0)
        parent = parent->suffix_link;
      if (parent->child.count(c))
        --i;
    }
  }
}

int main() {
  std::string text;
  std::getline(std::cin, text);
  int n;
  std::cin >> n;
  std::cin.ignore();
  std::vector<std::string> patterns(n);
  for (int i = 0; i < n; ++i) {
    std::getline(std::cin, patterns[i]);
  }
  trie_node* root = add_node();
  build_Trie(root, patterns);
  build_suffix_and_output_links(root);
  std::vector<std::vector<int>> indices(n);
  search_pattern(root, text, indices, patterns);
  for (int i = 0; i < n; ++i) {
    std::cout << indices[i].size() << ' ';
    for (int j = 0; j < indices[i].size(); ++j) {
      std::cout << indices[i][j] - patterns[i].size() + 2 << ' ';
    }
    std::cout << "\n";
  }
}
