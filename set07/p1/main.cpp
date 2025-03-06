#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using ll = long long;

struct Edge {
  int to;
  ll flow;
  ll cap;
  int rev;
};

int n, m;
std::vector<std::vector<Edge>> adj;
std::vector<int> start;
std::vector<int> level;

bool bfs() {
  std::fill(level.begin(), level.end(), -1);
  level[0] = 0;

  std::queue<int> q;
  q.push(0);

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (auto& e : adj[u]) {
      if (level[e.to] == -1 && e.flow < e.cap) {
        level[e.to] = level[u] + 1;
        q.push(e.to);
      }
    }
  }

  return level[n - 1] != -1;
}

ll dfs(int from, int to, ll flow) {
  if (from == to) {
    return flow;
  }

  for (; start[from] < adj[from].size(); start[from]++) {
    auto& e = adj[from][start[from]];
    if (level[e.to] == level[from] + 1 && e.flow < e.cap) {
      ll cur_flow = std::min(flow, e.cap - e.flow);
      ll temp_flow = dfs(e.to, to, cur_flow);

      if (temp_flow > 0) {
        e.flow += temp_flow;
        adj[e.to][e.rev].flow -= temp_flow;

        return temp_flow;
      }
    }
  }
  return 0;
}

int main() {
  std::cin >> n >> m;
  adj.resize(n);
  level.resize(n);
  start.resize(n);

  for (int i = 0; i < m; ++i) {
    int from, to, cap;
    std::cin >> from >> to >> cap;
    --to;
    --from;

    Edge from_to{to, 0, cap, static_cast<int>(adj[to].size())};
    Edge to_from{from, 0, 0, static_cast<int>(adj[from].size())};
    adj[from].emplace_back(std::move(from_to));
    adj[to].emplace_back(std::move(to_from));
  }

  ll ans{};
  while (bfs()) {
    std::fill(start.begin(), start.end(), 0);

    for (ll dfs_res = dfs(0, n - 1, LLONG_MAX); dfs_res; dfs_res = dfs(0, n - 1, LLONG_MAX)) {
      ans += dfs_res;
    }
  }

  std::cout << ans;
}