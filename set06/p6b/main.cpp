#include <climits>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

int cost(int v) {
  return v / 1000 + v / 100 % 10 + v / 10 % 10 + v % 10;
}

int main() {
  int n, a, b;
  std::cin >> n >> a >> b;

  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
  std::vector<int> d(n + 10, INT_MAX);
  std::vector<int> p(n + 10);
  d[a] = 0;
  p[a] = -1;
  pq.emplace(0, a);

  while (!pq.empty()) {
    int v = pq.top().second;
    pq.pop();

    std::string s = std::to_string(v);

    for (int i = 0; i < s.size(); ++i) {
      int diff = 0;
      for (int j = i; j < s.size(); ++j) {
        diff = diff * 10 + (s[j] - '0');
        if (diff == 0) {
          continue;
        }

        if (v + diff <= n) {
          if (d[v] + cost(diff) < d[v + diff]) {
            d[v + diff] = d[v] + cost(diff);
            p[v + diff] = v;
            pq.emplace(d[v + diff], v + diff);
          }
        }

        if (v - diff >= 0) {
          if (d[v] + cost(diff) < d[v - diff]) {
            d[v - diff] = d[v] + cost(diff);
            p[v - diff] = v;
            pq.emplace(d[v - diff], v - diff);
          }
        }
      }
    }
  }

  if (d[b] == INT_MAX) {
    std::cout << -1;
  } else {
    std::cout << d[b] << '\n';

    std::vector<std::string> path;
    int cur = b;
    while (p[cur] != -1) {
      int dist = cur - p[cur];
      if (dist < 0) {
        path.push_back(std::to_string(dist));
      } else {
        path.push_back('+' + std::to_string(dist));
      }
      cur = p[cur];
    }

    std::cout << path.size() << '\n';
    for (auto it = path.rbegin(); it != path.rend(); ++it) {
      std::cout << *it << '\n';
    }
  }
}