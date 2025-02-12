#include <algorithm>
#include <iostream>
#include <tuple>
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
        auto it = count_map.find(b[j]);
        if (it != count_map.end()) {
          --it->second;
          if (it->second == 0) {
            --count;
          }
        }

        if (count == 0) {
          break;
        }

        if (j >= mid - 1) {
          auto it = count_map.find(b[j - mid + 1]);
          if (it != count_map.end()) {
            ++it->second;
            if (it->second == 1) {
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

std::tuple<bool, int, int> binok2(int mid) {
  std::unordered_map<int, int> count_a, count_b, cur_count_b;

  for (int i = 0; i < mid; ++i) {
    ++count_a[a[i]];
  }

  for (int i = 0; i < mid; ++i) {
    ++count_b[b[i]];
  }

  if (count_a == count_b) {
    return {true, 1, 1};
  }

  for (int i = mid; i < n; ++i) {
    --count_a[a[i - mid]];
    if (count_a[a[i - mid]] == 0) {
      count_a.erase(a[i - mid]);
    }
    ++count_a[a[i]];
    cur_count_b = count_b;

    if (cur_count_b == count_a) {
      return {true, i - mid + 2, 1};
    }

    for (int j = mid; j < m; ++j) {
      --cur_count_b[b[j - mid]];
      if (cur_count_b[b[j - mid]] == 0) {
        cur_count_b.erase(b[j - mid]);
      }
      ++cur_count_b[b[j]];

      if (cur_count_b == count_a) {
        return {true, i - mid + 2, j - mid + 2};
      }
    }
  }

  return {false, -1, -1};
}

std::tuple<bool, int, int> binok3(int mid) {
  std::unordered_map<size_t, int> hash_a;

  size_t xor_a = 0;
  size_t sum_a = 0;
  for (int i = 0; i < mid; ++i) {
    xor_a ^= static_cast<size_t>(a[i]);
    sum_a += static_cast<size_t>(a[i]);
  }
  hash_a[xor_a + sum_a * 1337] = 1;

  for (int i = mid; i < n; ++i) {
    xor_a ^= static_cast<size_t>(a[i - mid]);
    xor_a ^= static_cast<size_t>(a[i]);
    sum_a -= static_cast<size_t>(a[i - mid]);
    sum_a += static_cast<size_t>(a[i]);
    hash_a[xor_a + sum_a * 1337] = i - mid + 2;
  }

  size_t xor_b = 0;
  size_t sum_b = 0;
  for (int i = 0; i < mid; ++i) {
    xor_b ^= static_cast<size_t>(b[i]);
    sum_b += static_cast<size_t>(b[i]);
  }

  if (hash_a.find(xor_b + sum_b * 1337) != hash_a.end()) {
    return {true, hash_a[xor_b + sum_b * 1337], 1};
  }

  for (int i = mid; i < m; ++i) {
    xor_b ^= static_cast<size_t>(b[i - mid]);
    xor_b ^= static_cast<size_t>(b[i]);
    sum_b -= static_cast<size_t>(b[i - mid]);
    sum_b += static_cast<size_t>(b[i]);

    if (hash_a.find(xor_b + sum_b * 1337) != hash_a.end()) {
      return {true, hash_a[xor_b + sum_b * 1337], i - mid + 2};
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
    auto [ok, i, j] = binok3(mid);
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