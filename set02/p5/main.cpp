#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

using Point = std::pair<long long, long long>;
using PointsVec = std::vector<Point>;

long long FindClosestPairDaC(const PointsVec& x) {
  if (x.size() <= 10) {
    long long res{LLONG_MAX};
    for (size_t i = 0; i < x.size(); ++i) {
      for (size_t j = i + 1; j < x.size(); ++j) {
        res = std::min(res, (x[j].first - x[i].first) * (x[j].first - x[i].first) +
                                (x[j].second - x[i].second) * (x[j].second - x[i].second));
      }
    }
    return res;
  }

  size_t mid{x.size() / 2};
  long long mid_x{x[mid].first};
  PointsVec x_l{};
  PointsVec x_r{};
  x_l.reserve(mid + 1);
  x_r.reserve(mid + 1);
  std::copy(x.begin(), x.begin() + mid, std::back_inserter(x_l));
  std::copy(x.begin() + mid, x.end(), std::back_inserter(x_r));

  long long delta = std::min(FindClosestPairDaC(x_l), FindClosestPairDaC(x_r));
  double sqrt_delta = std::sqrt(delta);

  PointsVec y{};
  y.reserve(static_cast<size_t>(std::sqrt(x.size())));
  for (const auto& point : x) {
    if (mid_x - sqrt_delta - 1 <= point.first && point.first <= mid_x + sqrt_delta + 1) {
      y.emplace_back(point);
    }
  }
  std::sort(y.begin(), y.end(), [](const auto& a, const auto& b) { return a.second < b.second; });

  for (size_t i = 0; i < y.size(); ++i) {
    for (size_t j = i + 1; j < i + 8 && j < y.size(); ++j) {  // fix here!!!!!
      delta = std::min(delta, (y[j].first - y[i].first) * (y[j].first - y[i].first) +
                                  (y[j].second - y[i].second) * (y[j].second - y[i].second));
    }
  }

  return delta;
}

// double stupid(const PointsVec& x) {
//   double res{1e100};
//   for (size_t i = 0; i < x.size(); ++i) {
//     for (size_t j = i + 1; j < x.size(); ++j) {
//       res = std::min(res, std::sqrt((x[j].first - x[i].first) * (x[j].first - x[i].first) +
//                                     (x[j].second - x[i].second) * (x[j].second - x[i].second)));
//     }
//   }
//   return res;
// }

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  PointsVec arr_x{};
  double mx{};
  for (long long x, y; std::cin >> x;) {
    std::cin >> y;
    arr_x.emplace_back(x, y);
    mx = std::max(mx, std::sqrt(x * x + y * y));
  }

  std::sort(arr_x.begin(), arr_x.end(), [](const auto& a, const auto& b) { return a.first < b.first; });
  std::cout << static_cast<long long>(std::sqrt(FindClosestPairDaC(arr_x))) << '\n';
  return 0;
}