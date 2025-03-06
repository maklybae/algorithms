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

int n, m, s, t;
std::vector<std::vector<Edge>> adj;
std::vector<int> start;
std::vector<int> level;

bool bfs() {
  std::fill(level.begin(), level.end(), -1);
  level[s] = 0;

  std::queue<int> q;
  q.push(s);

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

  return level[t] != -1;
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
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> m >> s >> t;
  --s;
  --t;
  adj.resize(n);
  level.resize(n);
  start.resize(n);

  for (int i = 0; i < m; ++i) {
    int from, to;
    std::cin >> from >> to;
    --to;
    --from;

    Edge from_to{to, 0, 1, static_cast<int>(adj[to].size())};
    Edge to_from{from, 0, 0, static_cast<int>(adj[from].size())};
    adj[from].emplace_back(std::move(from_to));
    adj[to].emplace_back(std::move(to_from));
  }

  ll ans{};
  while (bfs()) {
    std::fill(start.begin(), start.end(), 0);

    for (ll dfs_res = dfs(s, t, LLONG_MAX); dfs_res; dfs_res = dfs(s, t, LLONG_MAX)) {
      ans += dfs_res;
    }
  }

  if (ans >= 2) {
    std::cout << "YES\n";
    std::vector<int> path1{t};
    std::vector<int> path2{t};
    while (path1.back() != s) {
      for (auto& e : adj[path1.back()]) {
        if (e.flow == -1) {
          path1.emplace_back(e.to);
          e.flow = 0;
          break;
        }
      }
    }
    while (path2.back() != s) {
      for (auto& e : adj[path2.back()]) {
        if (e.flow == -1) {
          path2.emplace_back(e.to);
          break;
        }
      }
    }
    for (int i = path1.size() - 1; i >= 0; --i) {
      std::cout << path1[i] + 1 << ' ';
    }
    std::cout << '\n';
    for (int i = path2.size() - 1; i >= 0; --i) {
      std::cout << path2[i] + 1 << ' ';
    }
  } else {
    std::cout << "NO";
  }
}