#include <iostream>

size_t t{};
size_t f{};

void NestedLoops(size_t n) {
  size_t x = 100;
  size_t y = 0;
  for (size_t outer = 1; outer <= n; outer *= 2) {
    x = x + outer;
    for (size_t inner = 2; inner < n; ++inner) {
      if (x > y / inner) {
        y = y + outer / inner;
        ++t;
      } else {
        --y;
        ++f;
      }
    }
  }
}

int main() {
  for (size_t n = 1; n < 9223372036854775808ll; n *= 2) {
    t = 0;
    f = 0;
    NestedLoops(n);
    std::cout << n << ' ' << t << ' ' << f << '\n';
  }
}