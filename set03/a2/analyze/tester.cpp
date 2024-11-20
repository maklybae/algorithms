#include "tester.h"

#include <vector>

SortTesterResult SortTester::TestMerge(size_t size) {
  SortTesterResult result{};

  std::vector<int> random = generator_.Random(size);
  std::vector<int> reversed = generator_.Reversed(size);
  std::vector<int> nearly_sorted = generator_.NearlySorted(size);

  auto start = std::chrono::high_resolution_clock::now();
  MergeSort(random);
  auto end = std::chrono::high_resolution_clock::now();
  result.random_time = std::chrono::duration_cast<Ms>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  MergeSort(reversed);
  end = std::chrono::high_resolution_clock::now();
  result.reversed_time = std::chrono::duration_cast<Ms>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  MergeSort(nearly_sorted);
  end = std::chrono::high_resolution_clock::now();
  result.nearly_sorted_time = std::chrono::duration_cast<Ms>(end - start).count();

  return result;
}

SortTesterResult SortTester::TestMergeInsertion(size_t threshold, size_t size) {
  SortTesterResult result{};
  MergeInsertionSorter sorter;
  sorter.threshold = threshold;

  std::vector<int> random = generator_.Random(size);
  std::vector<int> reversed = generator_.Reversed(size);
  std::vector<int> nearly_sorted = generator_.NearlySorted(size);

  auto start = std::chrono::high_resolution_clock::now();
  sorter.MergeInsertionSort(random);
  auto end = std::chrono::high_resolution_clock::now();
  result.random_time = std::chrono::duration_cast<Ms>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  sorter.MergeInsertionSort(reversed);
  end = std::chrono::high_resolution_clock::now();
  result.reversed_time = std::chrono::duration_cast<Ms>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  sorter.MergeInsertionSort(nearly_sorted);
  end = std::chrono::high_resolution_clock::now();
  result.nearly_sorted_time = std::chrono::duration_cast<Ms>(end - start).count();

  return result;
}