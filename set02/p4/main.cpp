#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>

bool check(const std::vector<long long>& speeds, double time, long long l) {
  long long i_part = std::floor(time);
  double f_part = time - i_part;

  double dist_first{};
  for (size_t i = 0; i < i_part; ++i) {
    dist_first += speeds[i];
  }
  dist_first += speeds[i_part] * f_part;
  f_part = 1 - f_part;
  double dist_second{};
  for (long long i = i_part; i < speeds.size(); ++i) {
    dist_first += speeds[i] * f_part;
    dist_second += speeds[i - i_part] * f_part;
    if (dist_first - dist_second < l) {
      return false;
    }
    if (i + 1 >= speeds.size()) {
      break;
    }
    f_part = 1 - f_part;
    dist_first += speeds[i + 1] * f_part;
    dist_second += speeds[i - i_part] * f_part;
    if (dist_first - dist_second < l) {
      return false;
    }
    f_part = 1 - f_part;
  }
  return true;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  long long l{};
  std::cin >> l;
  size_t n{};
  std::cin >> n;
  std::vector<long long> speeds{};
  speeds.reserve(1000 * n);

  for (size_t i = 0; i < n; ++i) {
    long long dur{};
    long long speed{};
    std::cin >> dur >> speed;
    for (size_t j = 0; j < dur; ++j) {
      speeds.emplace_back(speed);
    }
  }

  double left{};
  double right = speeds.size();
  for (int i = 0; i < 200; ++i) {
    auto mid = (left + right) / 2;
    if (check(speeds, mid, l)) {
      right = mid;
    } else {
      left = mid;
    }
  }
  std::cout << std::fixed << std::setprecision(3) << right << '\n';
  return 0;
}
// #include <algorithm>
// #include <climits>
// #include <iomanip>
// #include <iostream>
// #include <utility>
// #include <vector>

// bool check(const std::vector<std::pair<long long, long long>>& dist_speed, double time, long long l) {
//   long long i_part = static_cast<long long>(time);
//   double f_part = time - i_part;

//   double dist_first = dist_speed[i_part].first;
//   if (i_part + 1 < dist_speed.size()) {
//     dist_first += dist_speed[i_part + 1].second * f_part;
//   }
//   f_part = 1 - f_part;
//   double dist_second{};
//   for (long long i = i_part + 1; i < dist_speed.size() - 1; ++i) {
//     dist_first += dist_speed[i].second * f_part;
//     dist_second += dist_speed[i - i_part].second * f_part;
//     if (dist_first - dist_second < l) {
//       return false;
//     }
//     f_part = 1 - f_part;
//     dist_first += dist_speed[i + 1].second * f_part;
//     dist_second += dist_speed[i - i_part + 1].second * f_part;
//     if (dist_first - dist_second < l) {
//       return false;
//     }
//     f_part = 1 - f_part;
//   }

//   // for (long long i = i_part; i < dist_speed.size() - 1; ++i) {
//   //   double delta = dist_speed[i].first + dist_speed[i + 1].second * f_part -
//   //                  (dist_speed[i - i_part].first + dist_speed[i + 1 - i_part].second * f_part);
//   //   // double delta = dist_speed[i].first - dist_speed[i - i_part].first +
//   //   //                f_part * (dist_speed[i + 1].second - dist_speed[i + 1 - i_part].second);
//   //   if (delta < l) {
//   //     return false;
//   //   }
//   // }
//   return true;
// }

// int main() {
//   std::ios::sync_with_stdio(false);
//   std::cin.tie(nullptr);
//   long long l{};
//   std::cin >> l;
//   size_t n{};
//   std::cin >> n;
//   std::vector<std::pair<long long, long long>> dist_speed{};
//   dist_speed.reserve(1000 * n + 1);
//   dist_speed.emplace_back();

//   for (size_t i = 0; i < n; ++i) {
//     long long dur{};
//     long long speed{};
//     std::cin >> dur >> speed;
//     for (size_t j = 0; j < dur; ++j) {
//       dist_speed.emplace_back(dist_speed.back().first + speed, speed);
//     }
//   }

//   dist_speed.erase(dist_speed.begin());

//   // check(dist_speed, 41.31, l);

//   double left{};
//   double right = dist_speed.size();
//   for (int i = 0; i < 400; ++i) {
//     auto mid = (left + right) / 2;
//     if (check(dist_speed, mid, l)) {
//       right = mid;
//     } else {
//       left = mid;
//     }
//   }
//   std::cout << std::fixed << std::setprecision(3) << left << '\n';
//   return 0;
// }
