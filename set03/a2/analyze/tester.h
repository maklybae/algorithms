#ifndef TESTER_H
#define TESTER_H

#include "generator.h"
#include "sort.h"

struct SortTesterResult {
  long long random_time;
  long long reversed_time;
  long long nearly_sorted_time;
};

class SortTester {
 private:
  using Ms = std::chrono::microseconds;

  ArrayGenerator generator_;

 public:
  SortTester(int min_val, int max_val, size_t max_size, double nearly_sorted_factor, int seed)
      : generator_{min_val, max_val, max_size, nearly_sorted_factor, seed} {
  }

  SortTesterResult TestMerge(size_t size);
  SortTesterResult TestMergeInsertion(size_t threshold, size_t size);
};

#endif