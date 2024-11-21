#include <iostream>

#include "tester.h"

int main() {
  SortTester tester1{0, 6000, 10000, 0.01};
  SortTester tester2{0, 6000, 10000, 0.01};
  SortTester tester3{0, 6000, 10000, 0.01};

  for (size_t n = 500; n <= 10000; n += 100) {
    SortTesterResult quick_result1 = tester1.TestQuick(n);
    SortTesterResult quick_result2 = tester2.TestQuick(n);
    SortTesterResult quick_result3 = tester3.TestQuick(n);

    SortTesterResult intro_result1 = tester1.TestIntro(n);
    SortTesterResult intro_result2 = tester2.TestIntro(n);
    SortTesterResult intro_result3 = tester3.TestIntro(n);

    std::cout
        << n << " " << (quick_result1.random_time + quick_result2.random_time + quick_result3.random_time) / 3.0 << " "
        << (quick_result1.reversed_time + quick_result2.reversed_time + quick_result3.reversed_time) / 3.0 << " "
        << (quick_result1.nearly_sorted_time + quick_result2.nearly_sorted_time + quick_result3.nearly_sorted_time) /
               3.0
        << " " << (intro_result1.random_time + intro_result2.random_time + intro_result3.random_time) / 3.0 << " "
        << (intro_result1.reversed_time + intro_result2.reversed_time + intro_result3.reversed_time) / 3.0 << " "
        << (intro_result1.nearly_sorted_time + intro_result2.nearly_sorted_time + intro_result3.nearly_sorted_time) /
               3.0
        << '\n';
  }
  return 0;
}