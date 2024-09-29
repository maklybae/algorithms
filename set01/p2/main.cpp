#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

int main() {
  size_t n{};
  std::cin >> n;
  std::vector<int> vec(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> vec[i];
  }

  std::pair<int, std::vector<size_t>> mx{0, {0}};
  mx.second.reserve(n);
  for (size_t step = 1; step < n; ++step) {
    int cur{};
    for (size_t i = 0; i < n; ++i) {
      cur += (vec[i] != vec[(i + step) % n]);
    }
    if (cur > mx.first) {
      mx.first = cur;
      mx.second.clear();
      mx.second.push_back(step);
    } else if (cur == mx.first) {
      mx.second.push_back(step);
    }
  }

  auto new_end = std::unique(mx.second.begin(), mx.second.end(), [&vec](const auto& a, const auto& b) {
    for (size_t i = 0; i < vec.size(); ++i) {
      if (vec[(i + a) % vec.size()] != vec[(i + b) % vec.size()]) {
        return false;
      }
    }
    return true;
  });

  std::cout << std::distance(mx.second.begin(), new_end) << '\n';
}