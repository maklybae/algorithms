#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using Heuristic = std::function<int(int)>;
using WeightedTo = std::pair<int, int>;
using AdjList = std::vector<std::vector<WeightedTo>>;

int AStarCount = 0;

int AStar(const AdjList& adj_list, int start, int finish, Heuristic heuristic) {
  using PriorityNode = std::pair<int, int>;

  std::vector<int> dist(adj_list.size(), std::numeric_limits<int>::max());
  dist[start] = 0;
  std::priority_queue<PriorityNode, std::vector<PriorityNode>, std::greater<PriorityNode>> q;
  std::vector<bool> visited(adj_list.size());
  q.emplace(dist[start] + heuristic(start), start);

  while (!q.empty()) {
    auto [f, u] = q.top();
    q.pop();
    if (f != dist[u] + heuristic(u)) {
      continue;  // Skip outdated nodes. Need decrease-key operation.
    }
    ++AStarCount;
    visited[u] = true;

    if (u == finish) {
      return dist[u];
    }

    for (auto [v, w] : adj_list[u]) {
      int tentative_score = dist[u] + w;

      if (!visited[v] && tentative_score < dist[v]) {
        dist[v] = tentative_score;
        q.emplace(dist[v] + heuristic(v), v);
      }
    }
  }

  return -1;
}

int DijkstraCount = 0;

int Dijkstra(const AdjList& adj_list, int start, int finish) {
  using PriorityNode = std::pair<int, int>;

  std::vector<int> dist(adj_list.size(), std::numeric_limits<int>::max());
  dist[start] = 0;
  std::priority_queue<PriorityNode, std::vector<PriorityNode>, std::greater<PriorityNode>> q;
  q.emplace(dist[start], start);

  while (!q.empty()) {
    auto [d, u] = q.top();
    q.pop();

    if (d != dist[u]) {
      continue;  // Skip outdated nodes. Need decrease-key operation.
    }
    ++DijkstraCount;

    for (auto [v, w] : adj_list[u]) {
      int tentative_score = dist[u] + w;

      if (tentative_score < dist[v]) {
        dist[v] = tentative_score;
        q.emplace(dist[v], v);
      }
    }
  }

  return dist[finish];
}

int TestHeuristic(int v) {
  switch (v) {
    case 0:
      return 15;
    case 1:
      return 10;
    case 2:
      return 13;
    case 3:
      return 4;
    case 4:
      return 4;
    case 5:
      return 2;
    case 6:
      return 1;
    case 7:
      return 0;
  }
  return 0;
}

int main() {
  AdjList adj_list{{{1, 6}, {2, 5}, {3, 10}}, {{0, 6}, {4, 6}},         {{0, 5}, {4, 6}, {5, 7}}, {{0, 10}, {5, 6}},
                   {{1, 6}, {2, 6}, {6, 4}},  {{2, 7}, {3, 6}, {6, 6}}, {{4, 4}, {5, 6}, {7, 3}}, {{6, 3}}};

  std::cout << AStar(adj_list, 0, 7, TestHeuristic) << ' ' << AStarCount << '\n'
            << Dijkstra(adj_list, 0, 7) << ' ' << DijkstraCount << '\n';
}