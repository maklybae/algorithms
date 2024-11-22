#ifndef SORT_H
#define SORT_H

#include <algorithm>
#include <vector>

#include "random_utils.h"

template <typename T>
void Heapify(std::vector<T>& arr, long long k, long long heap_start, long long heap_end) {
  long long heap_size{heap_end - heap_start + 1};
  while (2 * k <= heap_size) {
    long long j = 2 * k;
    if (j < heap_size && arr[j + heap_start - 1] < arr[j + heap_start]) {
      ++j;
    }
    if (arr[k + heap_start - 1] >= arr[j + heap_start - 1]) {
      break;
    }
    std::swap(arr[k + heap_start - 1], arr[j + heap_start - 1]);
    k = j;
  }
}

template <typename T>
void BuildMaxHeap(std::vector<T>& arr, long long heap_start, long long heap_end) {
  for (long long k = (heap_end - heap_start + 1) / 2; k >= 1; --k) {
    Heapify(arr, k, heap_start, heap_end);
  }
}

template <typename T>
void HeapSort(std::vector<T>& arr, long long heap_start, long long heap_end) {
  BuildMaxHeap(arr, heap_start, heap_end);

  while (heap_end - heap_start > 0) {
    std::swap(arr[heap_start], arr[heap_end]);
    Heapify(arr, 1, heap_start, --heap_end);
  }
}

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
    HeapSort(arr, left, right);
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