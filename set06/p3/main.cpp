#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> dsu;

int Find(int x) {
  if (dsu[x] == x) {
    return x;
  }
  return dsu[x] = Find(dsu[x]);
}

void Union(int x, int y) {
  int root_x = Find(x);
  int root_y = Find(y);
  dsu[root_y] = root_x;
}

void Init(int m) {
  dsu.resize(m);
  for (int i = 0; i < m; ++i) {
    dsu[i] = i;
  }
}

struct Query {
  bool ask;
  int from;
  int to;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, k;
  std::cin >> n >> m >> k;

  // std::vector<std::unordered_set<int>> adj(n);
  int empty;
  for (int i = 0; i < m; ++i) {
    std::cin >> empty >> empty;
    // adj[from - 1].insert(to - 1);
    // adj[to - 1].insert(from - 1);
  }

  std::vector<Query> queries;
  queries.reserve(k);

  for (int i = 0; i < k; ++i) {
    std::string type;
    int from, to;
    std::cin >> type >> from >> to;
    queries.emplace_back(type == "ask", from - 1, to - 1);
  }

  Init(n);
  std::vector<char> ans;
  ans.reserve(k);
  for (auto it = queries.rbegin(); it != queries.rend(); ++it) {
    const auto& q = *it;
    if (q.ask) {
      ans.push_back(Find(q.from) == Find(q.to));
    } else {
      Union(q.from, q.to);
    }
  }

  for (auto it = ans.rbegin(); it != ans.rend(); ++it) {
    if (*it) {
      std::cout << "YES\n";
    } else {
      std::cout << "NO\n";
    }
  }
}