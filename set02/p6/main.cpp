#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

struct Point {
  long long x{};
  long long y{};
  long long z{};
  size_t num{};
};

using PointsVec = std::vector<Point>;
using AnsT = std::pair<long long, std::pair<Point, Point>>;

AnsT FindClosestPairDaC(const PointsVec& x) {
  if (x.size() <= 10) {
    AnsT res{LLONG_MAX, {}};
    for (size_t i = 0; i < x.size(); ++i) {
      for (size_t j = i + 1; j < x.size(); ++j) {
        auto cur = (x[j].x - x[i].x) * (x[j].x - x[i].x) + (x[j].y - x[i].y) * (x[j].y - x[i].y) +
                   (x[j].z - x[i].z) * (x[j].z - x[i].z);
        if (cur < res.first) {
          res = {cur, {x[j], x[i]}};
        }
      }
    }
    return res;
  }

  size_t mid{x.size() / 2};
  long long mid_x{x[mid].x};
  PointsVec x_l{};
  PointsVec x_r{};
  x_l.reserve(mid + 1);
  x_r.reserve(mid + 1);
  std::copy(x.begin(), x.begin() + mid, std::back_inserter(x_l));
  std::copy(x.begin() + mid, x.end(), std::back_inserter(x_r));

  AnsT ans_l = FindClosestPairDaC(x_l);
  AnsT ans_r = FindClosestPairDaC(x_r);
  AnsT ans = ans_l.first < ans_r.first ? ans_l : ans_r;
  double sqrt_delta = std::sqrt(ans.first);

  PointsVec y{};
  y.reserve(static_cast<size_t>(std::sqrt(x.size())));
  for (const auto& point : x) {
    if (mid_x - sqrt_delta <= point.x && point.x <= mid_x + sqrt_delta) {
      y.emplace_back(point);
    }
  }
  std::sort(y.begin(), y.end(), [](const auto& a, const auto& b) { return a.y < b.y; });

  for (size_t i = 0; i < y.size(); ++i) {
    for (size_t j = i + 1; j < i + 16 && j < y.size(); ++j) {  // fix here!!!!!
      auto cur = (y[j].x - y[i].x) * (y[j].x - y[i].x) + (y[j].y - y[i].y) * (y[j].y - y[i].y) +
                 (y[j].z - y[i].z) * (y[j].z - y[i].z);
      if (cur < ans.first) {
        ans = {cur, {y[j], y[i]}};
      }
    }
  }

  PointsVec z{};
  z.reserve(y.size());
  std::copy(y.begin(), y.end(), std::back_inserter(z));
  std::sort(z.begin(), z.end(), [](const auto& a, const auto& b) { return a.z < b.z; });

  for (size_t i = 0; i < y.size(); ++i) {
    for (size_t j = i + 1; j < i + 16 && j < z.size(); ++j) {  // fix here!!!!!
      auto cur = (z[j].x - z[i].x) * (z[j].x - z[i].x) + (z[j].y - z[i].y) * (z[j].y - z[i].y) +
                 (z[j].z - z[i].z) * (z[j].z - z[i].z);
      if (cur < ans.first) {
        ans = {cur, {z[j], z[i]}};
      }
    }
  }

  return ans;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  size_t n{};
  std::cin >> n;

  PointsVec arr_x{};
  arr_x.reserve(n);
  for (size_t i = 0; i < n; ++i) {
    long long x{}, y{}, z{};
    std::cin >> x >> y >> z;
    arr_x.emplace_back(x, y, z, i + 1);
  }

  std::sort(arr_x.begin(), arr_x.end(), [](const auto& a, const auto& b) { return a.x < b.x; });
  auto ans = FindClosestPairDaC(arr_x);
  std::cout << std::fixed << std::setprecision(5) << std::sqrt(ans.first) << '\n';
  std::cout << ans.second.first.num << ' ' << ans.second.second.num << '\n';
  return 0;
}