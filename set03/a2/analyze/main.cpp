#include <iostream>

#include "tester.h"

int main() {
  SortTester tester1{0, 6000, 10000, 0.01, 228};
  SortTester tester2{0, 6000, 10000, 0.01, 1337};
  SortTester tester3{0, 6000, 10000, 0.01, 52};

  for (size_t n = 500; n <= 10000; n += 100) {
    SortTesterResult merge_result1 = tester1.TestMerge(n);
    SortTesterResult merge_result2 = tester2.TestMerge(n);
    SortTesterResult merge_result3 = tester3.TestMerge(n);

    SortTesterResult merge_insertion5_result1 = tester1.TestMergeInsertion(5, n);
    SortTesterResult merge_insertion5_result2 = tester2.TestMergeInsertion(5, n);
    SortTesterResult merge_insertion5_result3 = tester3.TestMergeInsertion(5, n);

    SortTesterResult merge_insertion10_result1 = tester1.TestMergeInsertion(10, n);
    SortTesterResult merge_insertion10_result2 = tester2.TestMergeInsertion(10, n);
    SortTesterResult merge_insertion10_result3 = tester3.TestMergeInsertion(10, n);

    SortTesterResult merge_insertion20_result1 = tester1.TestMergeInsertion(20, n);
    SortTesterResult merge_insertion20_result2 = tester2.TestMergeInsertion(20, n);
    SortTesterResult merge_insertion20_result3 = tester3.TestMergeInsertion(20, n);

    SortTesterResult merge_insertion30_result1 = tester1.TestMergeInsertion(30, n);
    SortTesterResult merge_insertion30_result2 = tester2.TestMergeInsertion(30, n);
    SortTesterResult merge_insertion30_result3 = tester3.TestMergeInsertion(30, n);

    SortTesterResult merge_insertion50_result1 = tester1.TestMergeInsertion(50, n);
    SortTesterResult merge_insertion50_result2 = tester2.TestMergeInsertion(50, n);
    SortTesterResult merge_insertion50_result3 = tester3.TestMergeInsertion(50, n);

    SortTesterResult merge_insertion100_result1 = tester1.TestMergeInsertion(100, n);
    SortTesterResult merge_insertion100_result2 = tester2.TestMergeInsertion(100, n);
    SortTesterResult merge_insertion100_result3 = tester3.TestMergeInsertion(100, n);

    SortTesterResult merge_insertion200_result1 = tester1.TestMergeInsertion(200, n);
    SortTesterResult merge_insertion200_result2 = tester2.TestMergeInsertion(200, n);
    SortTesterResult merge_insertion200_result3 = tester3.TestMergeInsertion(200, n);

    SortTesterResult merge_insertion500_result1 = tester1.TestMergeInsertion(400, n);
    SortTesterResult merge_insertion500_result2 = tester2.TestMergeInsertion(400, n);
    SortTesterResult merge_insertion500_result3 = tester3.TestMergeInsertion(400, n);

    std::cout << n << " " << (merge_result1.random_time + merge_result2.random_time + merge_result3.random_time) / 3.0
              << " " << (merge_result1.reversed_time + merge_result2.reversed_time + merge_result3.reversed_time) / 3.0
              << " "
              << (merge_result1.nearly_sorted_time + merge_result2.nearly_sorted_time +
                  merge_result3.nearly_sorted_time) /
                     3.0
              << " "
              << (merge_insertion5_result1.random_time + merge_insertion5_result2.random_time +
                  merge_insertion5_result3.random_time) /
                     3.0
              << " "
              << (merge_insertion5_result1.reversed_time + merge_insertion5_result2.reversed_time +
                  merge_insertion5_result3.reversed_time) /
                     3.0
              << " "
              << (merge_insertion5_result1.nearly_sorted_time + merge_insertion5_result2.nearly_sorted_time +
                  merge_insertion5_result3.nearly_sorted_time) /
                     3.0
              << " "
              << (merge_insertion10_result1.random_time + merge_insertion10_result2.random_time +
                  merge_insertion10_result3.random_time) /
                     3.0
              << " "
              << (merge_insertion10_result1.reversed_time + merge_insertion10_result2.reversed_time +
                  merge_insertion10_result3.reversed_time) /
                     3.0
              << " "
              << (merge_insertion10_result1.nearly_sorted_time + merge_insertion10_result2.nearly_sorted_time +
                  merge_insertion10_result3.nearly_sorted_time) /
                     3.0
              << " "
              << (merge_insertion20_result1.random_time + merge_insertion20_result2.random_time +
                  merge_insertion20_result3.random_time) /
                     3.0
              << " "
              << (merge_insertion20_result1.reversed_time + merge_insertion20_result2.reversed_time +
                  merge_insertion20_result3.reversed_time) /
                     3.0
              << " "
              << (merge_insertion20_result1.nearly_sorted_time + merge_insertion20_result2.nearly_sorted_time +
                  merge_insertion20_result3.nearly_sorted_time) /
                     3.0
              << " "
              << (merge_insertion30_result1.random_time + merge_insertion30_result2.random_time +
                  merge_insertion30_result3.random_time) /
                     3.0
              << " "
              << (merge_insertion30_result1.reversed_time + merge_insertion30_result2.reversed_time +
                  merge_insertion30_result3.reversed_time) /
                     3.0
              << " "
              << (merge_insertion30_result1.nearly_sorted_time + merge_insertion30_result2.nearly_sorted_time +
                  merge_insertion30_result3.nearly_sorted_time) /
                     3.0
              << " "
              << (merge_insertion50_result1.random_time + merge_insertion50_result2.random_time +
                  merge_insertion50_result3.random_time) /
                     3.0
              << " "
              << (merge_insertion50_result1.reversed_time + merge_insertion50_result2.reversed_time +
                  merge_insertion50_result3.reversed_time) /
                     3.0
              << " "
              << (merge_insertion50_result1.nearly_sorted_time + merge_insertion50_result2.nearly_sorted_time +
                  merge_insertion50_result3.nearly_sorted_time) /
                     3.0
              << " "
              << (merge_insertion100_result1.random_time + merge_insertion100_result2.random_time +
                  merge_insertion100_result3.random_time) /
                     3.0
              << " "
              << (merge_insertion100_result1.reversed_time + merge_insertion100_result2.reversed_time +
                  merge_insertion100_result3.reversed_time) /
                     3.0
              << " "
              << (merge_insertion100_result1.nearly_sorted_time + merge_insertion100_result2.nearly_sorted_time +
                  merge_insertion100_result3.nearly_sorted_time) /
                     3.0
              << " "
              << (merge_insertion200_result1.random_time + merge_insertion200_result2.random_time +
                  merge_insertion200_result3.random_time) /
                     3.0
              << " "
              << (merge_insertion200_result1.reversed_time + merge_insertion200_result2.reversed_time +
                  merge_insertion200_result3.reversed_time) /
                     3.0
              << " "
              << (merge_insertion200_result1.nearly_sorted_time + merge_insertion200_result2.nearly_sorted_time +
                  merge_insertion200_result3.nearly_sorted_time) /
                     3.0
              << " "
              << (merge_insertion500_result1.random_time + merge_insertion500_result2.random_time +
                  merge_insertion500_result3.random_time) /
                     3.0
              << " "
              << (merge_insertion500_result1.reversed_time + merge_insertion500_result2.reversed_time +
                  merge_insertion500_result3.reversed_time) /
                     3.0
              << " "
              << (merge_insertion500_result1.nearly_sorted_time + merge_insertion500_result2.nearly_sorted_time +
                  merge_insertion500_result3.nearly_sorted_time) /
                     3.0
              << '\n';
  }
}