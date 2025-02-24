#include <iostream>
#include <stack>
#include <vector>

int n, m;
std::stack<int> finished;
std::vector<std::vector<int>> adj;
std::vector<std::vector<int>> transposed;
std::vector<bool> visited;
std::vector<int> ans;

int neg(int x) {
  return -x - 1;
}

int abs(int x) {
  if (x < 0) {
    return -x - 1;
  }
  return x;
}

void dfs1(int u) {
  visited[u + n] = true;
  for (int v : adj[u + n]) {
    if (!visited[v + n]) {
      dfs1(v);
    }
  }
  finished.emplace(u);
}

void dfs2(int u) {
  visited[u + n] = true;
  if (ans[abs(u)] == -1) {
    if (u < 0) {
      ans[neg(u)] = 1;
    } else {
      ans[u] = 0;
    }
  }
  for (int v : transposed[u + n]) {
    if (!visited[v + n]) {
      dfs2(v);
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  while (std::cin >> n >> m) {
    finished = std::stack<int>();
    adj = std::vector<std::vector<int>>(2 * n);
    transposed = std::vector<std::vector<int>>(2 * n);
    visited = std::vector<bool>(2 * n);
    ans = std::vector<int>(n, -1);

    for (int i = 0; i < m; ++i) {
      int i1, i2;
      bool e1, e2;
      std::cin >> i1 >> e1 >> i2 >> e2;

      if (!e1) {
        i1 = neg(i1);
      }
      if (!e2) {
        i2 = neg(i2);
      }

      adj[neg(i1) + n].push_back(i2);
      adj[neg(i2) + n].push_back(i1);

      transposed[i2 + n].push_back(neg(i1));
      transposed[i1 + n].push_back(neg(i2));
    }

    for (int u = -n; u < n; ++u) {
      if (!visited[u + n]) {
        dfs1(u);
      }
    }

    visited = std::vector<bool>(2 * n);
    while (!finished.empty()) {
      if (!visited[finished.top() + n]) {
        dfs2(finished.top());
      }
      finished.pop();
    }

    for (int i = 0; i < n; ++i) {
      std::cout << ans[i];
    }
    std::cout << '\n';
  }
}