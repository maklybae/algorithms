#include <iostream>
#include <stack>
#include <vector>

std::stack<int> finished;
std::vector<std::vector<int>> adj;
std::vector<std::vector<int>> transposed;
std::vector<bool> visited;
std::vector<int> ans;

void dfs1(int u) {
  visited[u] = true;
  for (int v : adj[u]) {
    if (!visited[v]) {
      dfs1(v);
    }
  }
  finished.emplace(u);
}

void dfs2(int u, int scc) {
  visited[u] = true;
  ans[u] = scc;
  for (int v : transposed[u]) {
    if (!visited[v]) {
      dfs2(v, scc);
    }
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  adj.resize(n);
  transposed.resize(n);

  for (int i = 0; i < m; ++i) {
    int from, to;
    std::cin >> from >> to;

    adj[from - 1].emplace_back(to - 1);
    transposed[to - 1].emplace_back(from - 1);
  }

  visited.resize(n);
  for (int u = 0; u < n; ++u) {
    if (!visited[u]) {
      dfs1(u);
    }
  }

  ans.resize(n);
  visited = std::vector<bool>(n);
  int cur_scc = 1;
  while (!finished.empty()) {
    if (!visited[finished.top()]) {
      dfs2(finished.top(), cur_scc++);
    }
    finished.pop();
  }

  std::cout << --cur_scc << '\n';
  for (int a : ans) {
    std::cout << a << ' ';
  }
}