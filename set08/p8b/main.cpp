#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

struct trie_node {
  std::map<char, trie_node*> child;
  trie_node* suffix_link;
  trie_node* parent;
  char parent_char;
  bool is_terminal = false;
  bool bad = false;
  std::vector<trie_node*> good_transitions;
};

trie_node* add_node(trie_node* parent = nullptr, char c = 0) {
  trie_node* node = new trie_node;
  node->suffix_link = nullptr;
  node->parent = parent;
  node->parent_char = c;
  return node;
}

void build_trie(trie_node* root, const std::vector<std::string>& patterns) {
  for (const auto& s : patterns) {
    trie_node* cur = root;
    for (char c : s) {
      if (!cur->child.count(c)) {
        cur->child[c] = add_node(cur, c);
      }
      cur = cur->child[c];
    }
    cur->is_terminal = true;
  }
}

void build_suffix_links(trie_node* root) {
  root->suffix_link = root;
  std::queue<trie_node*> q;
  for (auto& [c, node] : root->child) {
    node->suffix_link = root;
    q.push(node);
  }
  while (!q.empty()) {
    trie_node* v = q.front();
    q.pop();
    for (auto& [c, u] : v->child) {
      trie_node* f = v->suffix_link;
      while (f != root && !f->child.count(c)) {
        f = f->suffix_link;
      }
      if (f->child.count(c) && f->child[c] != u)
        u->suffix_link = f->child[c];
      else
        u->suffix_link = root;
      q.push(u);
    }
  }
}

void mark_bad(trie_node* root) {
  std::queue<trie_node*> q;
  q.push(root);
  while (!q.empty()) {
    trie_node* v = q.front();
    q.pop();
    if (v->is_terminal || (v->suffix_link && v->suffix_link->bad)) {
      v->bad = true;
    }
    for (auto& [c, u] : v->child) {
      q.push(u);
    }
  }
}

void build_good_graph(trie_node* root, std::vector<trie_node*>& nodes) {
  std::queue<trie_node*> q;
  q.push(root);
  while (!q.empty()) {
    trie_node* v = q.front();
    q.pop();
    nodes.push_back(v);
    if (v->bad)
      continue;
    for (char c = '0'; c <= '1'; ++c) {
      trie_node* u = v;
      while (u != root && !u->child.count(c)) {
        u = u->suffix_link;
      }
      if (u->child.count(c))
        u = u->child[c];
      if (!u->bad)
        v->good_transitions.push_back(u);
    }
    for (auto& [c, u] : v->child) {
      q.push(u);
    }
  }
}

bool dfs_cycle(trie_node* v, std::set<trie_node*>& visiting, std::set<trie_node*>& visited) {
  visiting.insert(v);
  for (auto u : v->good_transitions) {
    if (visiting.count(u))
      return true;
    if (!visited.count(u) && dfs_cycle(u, visiting, visited))
      return true;
  }
  visiting.erase(v);
  visited.insert(v);
  return false;
}

int main() {
  int m;
  std::cin >> m;
  std::vector<std::string> patterns(m);
  for (int i = 0; i < m; ++i)
    std::cin >> patterns[i];

  trie_node* root = add_node();
  build_trie(root, patterns);
  build_suffix_links(root);
  mark_bad(root);

  std::vector<trie_node*> nodes;
  build_good_graph(root, nodes);

  std::set<trie_node*> visiting, visited;
  bool has_cycle = dfs_cycle(root, visiting, visited);

  std::cout << (has_cycle ? "TAK" : "NIE") << std::endl;

  return 0;
}