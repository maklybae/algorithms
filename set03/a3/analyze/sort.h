#ifndef SORT_H
#define SORT_H

#include <algorithm>
#include <vector>

#include "random_utils.h"

template <typename T>
void IntroSort(std::vector<T>& arr, long long left, long long right, long long depth_limit) {
  if (left >= right) {
    return;
  }

  if (right - left + 1 <= 16) {
    // Insertion Sort
    for (size_t i = left + 1; i <= right; ++i) {
      T key = std::move(arr[i]);
      long long j = static_cast<long long>(i) - 1;

      while (j >= static_cast<long long>(left) && arr[j] > key) {
        arr[j + 1] = std::move(arr[j]);
        --j;
      }
      arr[j + 1] = std::move(key);
    }
  } else if (depth_limit == 0) {
    // Heap Sort
    std::make_heap(arr.begin() + left, arr.begin() + right + 1);
    std::sort_heap(arr.begin() + left, arr.begin() + right + 1);
  } else {
    // Quick Sort
    // Partition
    std::swap(arr[left + GetRandomEngine()() % (right - left + 1)], arr[right]);
    long long i = left;
    long long j = right - 1;
    while (i <= j) {
      while (arr[i] < arr[right]) {
        ++i;
      }
      while (j > left && arr[j] > arr[right]) {
        --j;
      }
      if (i >= j) {
        break;
      }
      std::swap(arr[i++], arr[j--]);
    }
    std::swap(arr[i], arr[right]);

    // Recursive calls
    IntroSort(arr, left, i - 1, depth_limit - 1);
    IntroSort(arr, i + 1, right, depth_limit - 1);
  }
}

template <typename T>
void QuickSort(std::vector<T>& arr, long long left, long long right) {
  if (left >= right) {
    return;
  }

  // Partition
  std::swap(arr[left + GetRandomEngine()() % (right - left + 1)], arr[right]);
  long long i = left;
  long long j = right - 1;
  while (i <= j) {
    while (arr[i] < arr[right]) {
      ++i;
    }
    while (j > left && arr[j] > arr[right]) {
      --j;
    }
    if (i >= j) {
      break;
    }
    std::swap(arr[i++], arr[j--]);
  }
  std::swap(arr[i], arr[right]);

  // Recursive calls
  QuickSort(arr, left, i - 1);
  QuickSort(arr, i + 1, right);
}

#endif