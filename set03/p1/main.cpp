#include <algorithm>
#include <iostream>
#include <vector>

void heapify(std::vector<int>& arr, size_t k, size_t heap_size) {
  while (2 * k <= heap_size) {
    size_t j = 2 * k;
    if (j < heap_size && arr[j] < arr[j + 1]) {
      ++j;
    }
    if (arr[k] >= arr[j]) {
      break;
    }
    std::swap(arr[k], arr[j]);
    k = j;
  }
}

void buildMaxHeap(std::vector<int>& arr) {
  for (size_t k = (arr.size() - 1) / 2; k >= 1; --k) {
    heapify(arr, k, arr.size() - 1);
  }
}

void heapSort(std::vector<int>& arr) {
  buildMaxHeap(arr);

  size_t n{arr.size() - 1};
  while (n > 1) {
    std::swap(arr[1], arr[n]);
    heapify(arr, 1, --n);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  size_t n{};
  std::cin >> n;

  std::vector<int> arr(n + 1);
  for (size_t i = 1; i < n + 1; ++i) {
    std::cin >> arr[i];
  }

  heapSort(arr);

  for (size_t i = 1; i < n + 1; ++i) {
    std::cout << arr[i] << ' ';
  }
}