#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using ll = int;

struct Edge {
  int to;
  ll cap;
  int rev;
};

std::vector<int> rank;
std::vector<int> dsu;
std::vector<std::vector<Edge>> adj;
std::vector<int> start;
std::vector<int> level;
std::queue<int> q;

void make_set(int v) {
  for (int i = 0; i < v; ++i) {
    dsu[i] = i;
  }
}

int find_set(int v) {
  if (v == dsu[v]) {
    return v;
  }
  return dsu[v] = find_set(dsu[v]);
}

void union_sets(int a, int b) {
  a = find_set(a);
  b = find_set(b);
  if (a != b) {
    if (rank[a] < rank[b])
      std::swap(a, b);
    dsu[b] = a;
    if (rank[a] == rank[b])
      rank[a]++;
  }
}

bool bfs(int s, int t) {
  level.assign(adj.size(), -1);
  level[s] = 0;

  q.push(s);

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (auto& e : adj[u]) {
      if (level[e.to] == -1 && 0 < e.cap) {
        level[e.to] = level[u] + 1;
        q.push(e.to);
      }
    }
  }

  return level[t] != -1;
}

ll dfs(int from, int to, ll flow) {
  if (from == to) {
    return flow;
  }

  for (; start[from] < adj[from].size(); start[from]++) {
    auto& e = adj[from][start[from]];
    if (level[e.to] == level[from] + 1 && 0 < e.cap) {
      ll temp_flow = dfs(e.to, to, std::min(flow, e.cap));

      if (temp_flow > 0) {
        e.cap -= temp_flow;
        adj[e.to][e.rev].cap += temp_flow;

        return temp_flow;
      }
    }
  }
  return 0;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::string u, v;
  u.reserve(12);
  v.reserve(12);

  int n, m, k;
  std::cin >> n >> m >> k;
  // adj.resize(n);
  // level.resize(n);
  // start.resize(n);
  dsu.resize(n);
  rank.resize(n);
  make_set(n);
  std::vector<std::vector<Edge>> adj1(n), adj2(n);

  std::unordered_map<std::string, int> indicies;

  for (int i = 0; i < m; ++i) {
    std::cin >> u >> v;
    if (!indicies.count(u)) {
      indicies[u] = indicies.size();
    }
    if (!indicies.count(v)) {
      indicies[v] = indicies.size();
    }

    int from = indicies[u];
    int to = indicies[v];
    adj1[from].emplace_back(to, 1, static_cast<int>(adj1[to].size()));
    adj1[to].emplace_back(from, 1, static_cast<int>(adj1[from].size() - 1));
    adj2[from].emplace_back(to, 1, static_cast<int>(adj2[to].size()));
    adj2[to].emplace_back(from, 1, static_cast<int>(adj2[from].size() - 1));
    union_sets(from, to);
  }

  int count_poor = 0;
  for (int i = 0; i < k; ++i) {
    std::cin >> u >> v;
    int from = indicies[u];
    int to = indicies[v];

    if (count_poor >= 2 || from == to || find_set(from) != find_set(to)) {
      std::cout << 0 << '\n';
    } else {
      ++count_poor;
      ll ans{};
      if (count_poor == 1) {
        std::swap(adj, adj1);
      } else {
        std::swap(adj, adj2);
      }
      while (bfs(from, to)) {
        start.assign(n, 0);

        for (ll dfs_res = dfs(from, to, INT_MAX); dfs_res; dfs_res = dfs(from, to, INT_MAX)) {
          ans += dfs_res;
        }
      }

      std::cout << ans << '\n';
    }
  }
}
