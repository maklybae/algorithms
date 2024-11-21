#include "tester.h"

#include <vector>

#include "sort.h"

SortTesterResult SortTester::TestQuick(size_t size) {
  SortTesterResult result{};

  std::vector<int> random = generator_.Random(size);
  std::vector<int> reversed = generator_.Reversed(size);
  std::vector<int> nearly_sorted = generator_.NearlySorted(size);

  auto start = std::chrono::high_resolution_clock::now();
  QuickSort(random, 0, size - 1);
  auto end = std::chrono::high_resolution_clock::now();
  result.random_time = std::chrono::duration_cast<Ms>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  QuickSort(reversed, 0, size - 1);
  end = std::chrono::high_resolution_clock::now();
  result.reversed_time = std::chrono::duration_cast<Ms>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  QuickSort(nearly_sorted, 0, size - 1);
  end = std::chrono::high_resolution_clock::now();
  result.nearly_sorted_time = std::chrono::duration_cast<Ms>(end - start).count();

  return result;
}

SortTesterResult SortTester::TestIntro(size_t size) {
  SortTesterResult result{};

  std::vector<int> random = generator_.Random(size);
  std::vector<int> reversed = generator_.Reversed(size);
  std::vector<int> nearly_sorted = generator_.NearlySorted(size);
  auto param = static_cast<long long>(2 * std::log2(size));

  auto start = std::chrono::high_resolution_clock::now();
  IntroSort(random, 0, size - 1, param);
  auto end = std::chrono::high_resolution_clock::now();
  result.random_time = std::chrono::duration_cast<Ms>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  IntroSort(reversed, 0, size - 1, param);
  end = std::chrono::high_resolution_clock::now();
  result.reversed_time = std::chrono::duration_cast<Ms>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  IntroSort(nearly_sorted, 0, size - 1, param);
  end = std::chrono::high_resolution_clock::now();
  result.nearly_sorted_time = std::chrono::duration_cast<Ms>(end - start).count();

  return result;
}