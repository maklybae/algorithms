#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
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

  int n;
  std::cin >> n;

  std::vector<std::unordered_set<std::string>> juices(n);

  for (int i = 0; i < n; ++i) {
    int k;
    std::cin >> k;
    for (int j = 0; j < k; ++j) {
      std::string tmp;
      std::cin >> tmp;
      juices[i].emplace(std::move(tmp));
    }
  }
  std::sort(juices.begin(), juices.end(), [](const auto& a, const auto& b) { return a.size() < b.size(); });

  g.resize(n);
  for (int i = 0; i < n - 1; ++i) {
    for (int j = i + 1; j < n; ++j) {
      bool flag = true;
      for (const auto& component : juices[i]) {
        if (!juices[j].contains(component)) {
          flag = false;
          break;
        }
      }
      if (flag) {
        g[i].emplace_back(j);
      }
    }
  }

  mt.resize(n, -1);
  used.resize(g.size());
  int matching = 0;
  for (int v = 0; v < g.size(); ++v) {
    used.assign(n, false);
    // try_kuhn(v);
    matching += try_kuhn(v);
  }

  std::cout << n - matching;
}