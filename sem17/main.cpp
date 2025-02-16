#include <cassert>
#include <iostream>
#include <vector>

class Graph {
 public:
  explicit Graph(int n) : adj_list_(n), deg_(n) {
  }

  int CountVertex() const {
    return adj_list_.size();
  }

  int CountEdge() const {
    return count_edge_;
  }

  void addEdge(int u, int v) {
    adj_list_[u].emplace_back(count_edge_, v);
    adj_list_[v].emplace_back(count_edge_, u);
    ++count_edge_;
    ++deg_[u];
    ++deg_[v];
  }

  std::vector<int> EulerPath() const {
    if (!CheckEuler()) {
      return {};
    }

    int start = 0;
    for (int i = 0; i < CountVertex(); ++i) {
      if (deg_[i] % 2 == 1) {
        start = i;
        break;
      }
    }

    std::vector<bool> visited(count_edge_);
    std::vector<int> first(CountVertex());
    std::vector<int> path;
    path.reserve(CountVertex());

    EulerPathImpl(start, visited, first, path);
    return path;
  }

  bool CheckEuler() const {
    int odd_vertex{};
    for (auto x : deg_) {
      if (x % 2 == 1) {
        ++odd_vertex;
      }
    }
    if (odd_vertex > 2) {
      return false;
    }

    // Все компоненты связности, кроме, может быть, одной, не содержат ребер.
    std::vector<bool> visited(CountVertex());
    for (int i = 0; i < CountVertex(); ++i) {
      if (deg_[i] > 0) {
        Dfs(i, visited);
        break;
      }
    }

    for (int i = 0; i < CountVertex(); ++i) {
      if (deg_[i] > 0 && !visited[i]) {
        return false;
      }
    }
    return true;
  }

 private:
  void EulerPathImpl(int u, std::vector<bool>& visited, std::vector<int>& first, std::vector<int>& path) const {
    while (first[u] < adj_list_[u].size()) {
      auto [i, v] = adj_list_[u][first[u]++];
      if (!visited[i]) {
        visited[i] = true;
        EulerPathImpl(v, visited, first, path);
        path.push_back(v);
      }
    }
  }

  void Dfs(int v, std::vector<bool>& visited) const {
    visited[v] = true;
    for (auto adj : adj_list_[v]) {
      if (!visited[adj.second]) {
        Dfs(adj.second, visited);
      }
    }
  }

  using EdgeVertex = std::pair<int, int>;
  std::vector<std::vector<EdgeVertex>> adj_list_{};
  std::vector<int> deg_{};
  int count_edge_{0};
};

void TestCheckEuler() {
  // Test case 1: Graph with no edges
  Graph g1(3);
  assert(g1.CheckEuler() == true);

  // Test case 2: Graph with a single edge
  Graph g2(2);
  g2.addEdge(0, 1);
  assert(g2.CheckEuler() == true);

  // Test case 3: Graph with an Eulerian path
  Graph g3(3);
  g3.addEdge(0, 1);
  g3.addEdge(1, 2);
  assert(g3.CheckEuler() == true);

  // Test case 4: Graph with an Eulerian circuit
  Graph g4(3);
  g4.addEdge(0, 1);
  g4.addEdge(1, 2);
  g4.addEdge(2, 0);
  assert(g4.CheckEuler() == true);

  // Test case 5: Graph with an Eulerian path
  Graph g5(4);
  g5.addEdge(0, 1);
  g5.addEdge(1, 2);
  g5.addEdge(2, 3);
  assert(g5.CheckEuler() == true);

  Graph g6(4);
  g6.addEdge(0, 1);
  g6.addEdge(0, 2);
  g6.addEdge(0, 3);
  assert(g6.CheckEuler() == false);

  std::cout << "CheckEuler passed\n";
}

void CoutVector(const std::vector<int>& to_print) {
  for (auto x : to_print) {
    std::cout << x << ' ';
  }
  std::cout << '\n';
}

void TestEulerPath() {
  // Test case 2: Graph with a single edge
  Graph g2(2);
  g2.addEdge(0, 1);
  auto path2 = g2.EulerPath();
  CoutVector(path2);
  assert(path2.size() == 1);

  // Test case 3: Graph with an Eulerian path
  Graph g3(3);
  g3.addEdge(0, 1);
  g3.addEdge(1, 2);
  auto path3 = g3.EulerPath();
  CoutVector(path3);
  assert(path3.size() == 2);

  // Test case 4: Graph with an Eulerian circuit
  Graph g4(3);
  g4.addEdge(0, 1);
  g4.addEdge(1, 2);
  g4.addEdge(2, 0);
  auto path4 = g4.EulerPath();
  CoutVector(path4);
  assert(path4.size() == 3);

  // Test case 5: Graph with many isolated vertices
  Graph g5(10);
  g5.addEdge(0, 1);
  auto path5 = g5.EulerPath();
  CoutVector(path5);

  std::cout << "EulerPath passed\n";
}

int main() {
  TestCheckEuler();
  TestEulerPath();
  return 0;
}