#include <iostream>
#include <queue>
#include <vector>
class Network {
  using ll = long long;

 public:
  explicit Network(int n) : adj_(n) {
  }

  void AddEdge(int from, int to, ll cap) {
    adj_[from].push_back({to, 0, cap, static_cast<int>(adj_[to].size())});
    adj_[to].push_back({from, 0, 0, static_cast<int>(adj_[from].size() - 1)});
  }

  ll MaxFlow(int s, int t) {
    ll ans{};
    std::vector<int> start(adj_.size());
    std::vector<int> level(adj_.size());

    while (bfs(s, t, level)) {
      std::fill(start.begin(), start.end(), 0);

      for (ll dfs_res = dfs(s, t, LLONG_MAX, start, level); dfs_res; dfs_res = dfs(s, t, LLONG_MAX, start, level)) {
        ans += dfs_res;
      }
    }

    return ans;
  }

 private:
  struct Edge {
    int to;
    ll flow;
    ll cap;
    int rev;
  };

  bool bfs(int s, int t, std::vector<int>& level) {
    std::fill(level.begin(), level.end(), -1);
    level[s] = 0;

    std::queue<int> q;
    q.push(s);

    while (!q.empty()) {
      int u = q.front();
      q.pop();

      for (auto& e : adj_[u]) {
        if (level[e.to] == -1 && e.flow < e.cap) {
          level[e.to] = level[u] + 1;
          q.push(e.to);
        }
      }
    }

    return level[t] != -1;
  }

  ll dfs(int from, int to, ll flow, std::vector<int>& start, std::vector<int>& level) {
    if (from == to) {
      return flow;
    }

    for (; start[from] < adj_[from].size(); start[from]++) {
      auto& e = adj_[from][start[from]];
      if (level[e.to] == level[from] + 1 && e.flow < e.cap) {
        ll cur_flow = std::min(flow, e.cap - e.flow);
        ll temp_flow = dfs(e.to, to, cur_flow, start, level);

        if (temp_flow > 0) {
          e.flow += temp_flow;
          adj_[e.to][e.rev].flow -= temp_flow;

          return temp_flow;
        }
      }
    }
    return 0;
  }

  std::vector<std::vector<Edge>> adj_;
};

int main() {
  int n, m;
  std::cin >> n >> m;

  Network net(n);

  for (int i = 0; i < m; ++i) {
    int from, to, cap;
    std::cin >> from >> to >> cap;
    --to;
    --from;
    net.AddEdge(from, to, cap);
  }

  std::cout << net.MaxFlow(0, n - 1) << std::endl;
}