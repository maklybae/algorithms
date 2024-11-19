#include <algorithm>
#include <iostream>
#include <random>

struct Circle {
  double x{};
  double y{};
  double r{};

  Circle(double x, double y, double r) : x{x}, y{y}, r{r} {
  }

  bool CheckPoint(double x_test, double y_test) {
    return (x_test - x) * (x_test - x) + (y_test - y) * (y_test - y) <= r * r;
  }
};

int main() {
  int n{};
  std::cin >> n;

  double x{};
  double y{};
  double r{};
  std::cin >> x >> y >> r;
  auto c1 = Circle{x, y, r};
  std::cin >> x >> y >> r;
  auto c2 = Circle{x, y, r};
  std::cin >> x >> y >> r;
  auto c3 = Circle{x, y, r};

  double x_min{};
  double x_max{};
  double y_min{};
  double y_max{};
  std::cin >> x_min >> x_max >> y_min >> y_max;

  double rec_area = (x_max - x_min) * (y_max - y_min);

  std::mt19937 rnd_engine{};

  rnd_engine.seed(1312951);

  std::uniform_real_distribution x_distr{x_min, x_max};
  std::uniform_real_distribution y_distr{y_min, y_max};

  int count{};  // number of points in intersection

  for (int i = 0; i < n; ++i) {
    double x_test{x_distr(rnd_engine)};
    double y_test{y_distr(rnd_engine)};

    if (c1.CheckPoint(x_test, y_test) && c2.CheckPoint(x_test, y_test) && c3.CheckPoint(x_test, y_test)) {
      ++count;
    }
  }

  std::cout << static_cast<double>(count) / n * rec_area;

  return 0;
}