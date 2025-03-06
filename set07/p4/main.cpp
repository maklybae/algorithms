#include <iostream>
#include <vector>

std::vector<std::vector<int>> g;
std::vector<int> mt;
std::vector<bool> used;

bool try_kuhn(int v) {
  if (used[v]) {
    return false;
  }
  used[v] = true;

  for (int to : g[v]) {
    if (mt[to] == -1 || try_kuhn(mt[to])) {
      mt[to] = v;
      return true;
    }
  }
  return false;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, a, b;
  std::cin >> n >> m >> a >> b;

  int right_count = 0;
  std::vector<int> prev(m, -1);
  for (int i = 0; i < n; ++i) {
    std::vector<int> now(m, -1);
    for (int j = 0; j < m; ++j) {
      char ch;
      std::cin >> ch;
      if (ch == '*') {
        if ((i + j) % 2 == 0) {
          now[j] = g.size();
          g.emplace_back();
          if (j - 1 >= 0 && now[j - 1] != -1) {
            g.back().emplace_back(now[j - 1]);
          }
          if (prev[j] != -1) {
            g.back().emplace_back(prev[j]);
          }
        } else {
          now[j] = right_count++;
          if (j - 1 >= 0 && now[j - 1] != -1) {
            g[now[j - 1]].emplace_back(now[j]);
          }
          if (prev[j] != -1) {
            g[prev[j]].emplace_back(now[j]);
          }
        }
      }
    }
    prev = std::move(now);
  }

  int need = g.size() + right_count;
  if (a >= 2 * b) {
    std::cout << need * b;
    return 0;
  }

  mt.resize(right_count, -1);
  used.resize(g.size());
  int matching = 0;

  for (int v = 0; v < g.size(); ++v) {
    used.assign(n, false);
    try_kuhn(v);
    // matching += try_kuhn(v);
  }

  for (int val : mt) {
    if (val != -1) {
      ++matching;
    }
  }

  std::cout << matching * a + (need - 2 * matching) * b;
}