#include <algorithm>
#include <list>
#include <random>
#include <vector>

struct Edge {
  int u;
  int v;
  int weight;
};

class DSU {
 public:
  explicit DSU(int n);
  int Union(int x, int y);
  int Find(int x);
};

using Edges = std::vector<Edge>;
using AdjListItem = std::pair<int, int>;  // pair (to, weight)
using AdjLists = std::vector<std::list<AdjListItem>>;

Edges edges;   // массив ребер
AdjLists adj;  // списки смежности

void Dfs(int u, const AdjLists& adj, std::vector<bool>& visited) {
  visited[u] = true;
  for (auto [v, weight] : adj[u]) {
    if (!visited[v]) {
      Dfs(v, adj, visited);
    }
  }
}

bool IsConnected(const AdjLists& adj_matrix) {
  std::vector<bool> visited(adj_matrix.size());

  Dfs(0, adj_matrix, visited);

  for (bool v : visited) {
    if (!v) {
      return false;
    }
  }
  return true;
}

std::pair<AdjLists, int> ALG_1(Edges& edges, AdjLists adj) {
  AdjLists mst = std::move(adj);  // adj copied in function call
  std::sort(edges.begin(), edges.end(), [](auto e1, auto e2) { return e1.weight > e2.weight; });
  int cost = 0;

  for (auto [u, v, weight] : edges) {
    // remove edge uv from mst
    mst[u].remove({v, weight});
    mst[v].remove({u, weight});

    if (!IsConnected(mst)) {
      // add edge uv back to mst
      mst[u].emplace_back(v, weight);
      mst[v].emplace_back(u, weight);
      cost += weight;
    }
  }

  return {mst, cost};
}

std::pair<Edges, int> ALG_2(Edges& edges, int n) {
  std::shuffle(edges.begin(), edges.end(), std::default_random_engine{});
  Edges mst{};
  DSU dsu{n};
  int cost = 0;

  for (auto e : edges) {
    if (dsu.Find(e.u) != dsu.Find(e.v)) {
      mst.push_back(e);
      dsu.Union(e.u, e.v);
      cost += e.weight;
    }
  }

  return {mst, cost};
}

std::vector<int> FindCycle(int from) {
  std::vector<int> cycle;
  std::vector<bool> visited(adj.size());
  std::vector<int> parent(adj.size(), -1);

  std::function<bool(int)> dfs = [&](int u) {
    visited[u] = true;
    for (auto [v, weight] : adj[u]) {
      if (!visited[v]) {
        parent[v] = u;
        if (dfs(v)) {
          return true;
        }
      } else if (v != parent[u]) {
        cycle.push_back(u);
        for (int i = u; i != v; i = parent[i]) {
          cycle.push_back(i);
        }
        cycle.push_back(v);
        return true;
      }
    }
    return false;
  };

  dfs(from);
  return cycle;
}

std::pair<AdjLists, int> ALG_3(Edges& edges, int n) {
  AdjLists mst(n);
  std::shuffle(edges.begin(), edges.end(), std::default_random_engine{});
  DSU dsu{n};
  int cost = 0;

  for (auto e : edges) {
    if (dsu.Find(e.u) != dsu.Find(e.v)) {
      mst[e.u].emplace_back(e.v, e.weight);
      mst[e.v].emplace_back(e.u, e.weight);
    } else {
      auto cycle = FindCycle(e.u);
      int max_weight = 0;
      int to_remove_start = -1, to_remove_end = -1;
      for (int i = 0; i < cycle.size() - 1; ++i) {
        int u = cycle[i];
        int v = cycle[i + 1];
        int new_weight = std::find_if(edges.begin(), edges.end(), [&](auto e) {
                           return (e.u == u && e.v == v) || (e.u == v && e.v == u);
                         })->weight;
        if (new_weight > max_weight) {
          max_weight = new_weight;
          to_remove_start = u;
          to_remove_end = v;
        }
      }

      if (max_weight > e.weight) {
        mst[to_remove_start].remove({to_remove_end, max_weight});
        mst[to_remove_end].remove({to_remove_start, max_weight});
        mst[e.u].emplace_back(e.v, e.weight);
        mst[e.v].emplace_back(e.u, e.weight);
        cost += e.weight - max_weight;
      }
    }
  }

  return {mst, cost};
}
