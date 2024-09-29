#include <vector>

void selectionSort(std::vector<int> &A) {
  for (size_t i = 0; i < A.size(); ++i) {
    size_t minId = i;

    for (size_t j = i + 1; j < A.size(); ++j) {
      if (A[j] < A[minId]) {
        minId = j;
      }
    }

    std::swap(A[minId], A[i]);
  }
}