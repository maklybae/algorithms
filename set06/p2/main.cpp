#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

std::vector<int> dsu;

int Find(int x) {
  if (dsu[x] == x) {
    return x;
  }
  return Find(dsu[x]);
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

struct Edge {
  int from;
  int to;
  int weight;

  friend bool operator==(Edge, Edge) = default;
};

int main() {
  int n, m;
  std::cin >> n >> m;

  std::vector<Edge> e;
  e.reserve(m);
  for (int i = 0; i < m; ++i) {
    int from, to, weight;
    std::cin >> from >> to >> weight;

    e.emplace_back(from - 1, to - 1, weight);
  }

  std::sort(e.begin(), e.end(), [](Edge x, Edge y) { return x.weight < y.weight; });
  Init(m);

  std::vector<Edge> mst;
  mst.reserve(n - 1);

  int first_sum{};
  for (Edge edge : e) {
    if (Find(edge.from) != Find(edge.to)) {
      mst.push_back(edge);
      Union(edge.from, edge.to);
      first_sum += edge.weight;
    }
  }

  int best_second_sum{INT_MAX};
  for (Edge deleted_edge : mst) {
    Init(m);
    int second_sum{};
    for (Edge edge : e) {
      if (edge != deleted_edge) {
        if (Find(edge.from) != Find(edge.to)) {
          Union(edge.from, edge.to);
          second_sum += edge.weight;
        }
      }
    }
    best_second_sum = std::min(best_second_sum, second_sum);
  }

  std::cout << first_sum << ' ' << best_second_sum;
}