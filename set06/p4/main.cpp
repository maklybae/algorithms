#include <algorithm>
#include <climits>
#include <iostream>
#include <utility>
#include <vector>

struct Edge {
  long long from, to, weight;
};

int main() {
  long long n, m;
  std::cin >> n >> m;

  std::vector<Edge> e;
  e.reserve(m);
  for (long long i = 0; i < m; ++i) {
    long long from, to, weight;
    std::cin >> from >> to >> weight;

    e.emplace_back(from, to, weight);
  }

  std::vector<long long> d(n, LLONG_MAX);
  std::vector<long long> p(n, -1);
  d[0] = 0;
  for (long long i = 0; i < n - 1; ++i) {
    for (auto edge : e) {
      if (d[edge.from] < LLONG_MAX && d[edge.from] + edge.weight < d[edge.to]) {
        d[edge.to] = d[edge.from] + edge.weight;
        p[edge.to] = edge.from;
      }
    }
  }

  std::vector<bool> ans_inf(n);
  for (long long i = 0; i < n; ++i) {
    for (auto edge : e) {
      if (d[edge.from] < LLONG_MAX && d[edge.from] + edge.weight < d[edge.to]) {
        d[edge.to] = LLONG_MIN;
        ans_inf[edge.to] = true;
      }
      if (ans_inf[edge.from]) {
        ans_inf[edge.to] = true;
      }
    }
  }

  for (long long i = 1; i < n; ++i) {
    if (ans_inf[i]) {
      std::cout << "-inf\n";
    } else {
      std::cout << d[i] << '\n';
    }
  }
}