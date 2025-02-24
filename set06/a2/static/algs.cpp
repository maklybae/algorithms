#include <climits>
#include <queue>

using WeightAdj = std::pair<int, int>;
using AdjLists = std::vector<std::vector<WeightAdj>>;

std::vector<int> Dijkstra(const AdjLists& adj, int start) {
  std::priority_queue<WeightAdj, std::vector<WeightAdj>, std::greater<>> pq;
  std::vector<int> dist(adj.size(), INT_MAX);
  dist[start] = 1;
  pq.emplace(1, start);

  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();

    if (d > dist[u]) {
      continue;
    }

    for (const auto& [w, v] : adj[u]) {
      if (dist[v] > dist[u] * w) {
        dist[v] = dist[u] * w;
        pq.emplace(dist[v], v);
      }
    }
  }

  return dist;
}

using DistMatrix = std::vector<std::vector<int>>;

AdjLists RestoreGraph(DistMatrix dist) {
  AdjLists adj(dist.size());
  int n = dist.size();

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (dist[i][j] == INT_MAX || i == j) {
        continue;
      }

      bool edge = true;
      for (int k = 0; k < n; ++k) {
        if (k == i || k == j) {
          continue;
        }

        if (dist[i][j] == dist[i][k] + dist[k][j]) {
          edge = false;
        }
      }

      if (edge) {
        adj[i].emplace_back(dist[i][j], j);
      }
    }
  }

  return adj;
}