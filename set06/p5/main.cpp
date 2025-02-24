#include <climits>
#include <iostream>
#include <vector>
int main() {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<long long>> d(n, std::vector<long long>(n, LLONG_MAX));
  for (int i = 0; i < m; ++i) {
    int from, to, weight;
    std::cin >> from >> to >> weight;

    d[from][to] = weight;
  }

  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (d[i][k] < LLONG_MAX && d[k][j] < LLONG_MAX) {
          d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
        }
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i != j) {
        if (d[i][j] == LLONG_MAX) {
          d[i][j] = -1;
        }
        std::cout << i << ' ' << j << ' ' << d[i][j] << '\n';
      }
    }
  }
}