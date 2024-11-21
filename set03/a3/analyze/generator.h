#ifndef GENERATOR_H
#define GENERATOR_H

#include <algorithm>
#include <random>
#include <vector>

class ArrayGenerator {
 private:
  int min_val_{};
  int max_val_{};
  size_t max_size_{};
  double nearly_factor_{};  // 0 < x < 1, where 1 is n swaps
  std::vector<int> random_{};
  std::vector<int> reversed_{};
  std::vector<int> nearly_sorted_{};

  std::vector<int> GenerateRandomVec();
  void InitRandom();
  void InitReversed();
  void InitNearlySorted();

 public:
  ArrayGenerator(int min_val, int max_val, size_t max_size, double nearly_factor);
  std::vector<int> Random(size_t size);
  std::vector<int> Reversed(size_t size);
  std::vector<int> NearlySorted(size_t size);
};

#endif