#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

int n, m;
std::vector<int> a, b;

std::tuple<bool, int, int> binok(int mid) {
  std::unordered_map<int, int> count_fixed_map{}, count_map{};

  for (int i = 0; i < n; ++i) {
    ++count_fixed_map[a[i]];
    ++count_map[a[i]];

    if (i >= mid - 1) {
      int count = count_map.size();
      int j = 0;

      for (; j < m; ++j) {
        if (count_map.contains(b[j])) {
          --count_map[b[j]];
          if (count_map[b[j]] == 0) {
            --count;
          }
        }

        if (count == 0) {
          break;
        }

        if (j >= mid - 1) {
          if (count_map.contains(b[j - mid + 1])) {
            count_map[b[j - mid + 1]]++;
            if (count_map[b[j - mid + 1]] == 1) {
              ++count;
            }
          }
        }
      }

      if (j != m) {
        return {true, i - mid + 2, j - mid + 2};
      }

      for (auto [key, val] : count_map) {
        count_map[key] = count_fixed_map[key];
      }

      --count_fixed_map[a[i - mid + 1]];
      --count_map[a[i - mid + 1]];
      if (count_fixed_map[a[i - mid + 1]] == 0) {
        count_fixed_map.erase(a[i - mid + 1]);
        count_map.erase(a[i - mid + 1]);
      }
    }
  }

  return {false, -1, -1};
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n;
  a = std::vector<int>(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  std::cin >> m;
  b = std::vector<int>(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
  }

  int l = 0, r = std::min(n, m);  // check left bound
  int besti = -1, bestj = -1;
  while (l < r) {
    int mid = (l + r + 1) / 2;
    auto [ok, i, j] = binok(mid);
    if (ok) {
      l = mid;
      besti = i;
      bestj = j;
    } else {
      r = mid - 1;
    }
  }

  std::cout << l << ' ' << besti << ' ' << bestj;
}