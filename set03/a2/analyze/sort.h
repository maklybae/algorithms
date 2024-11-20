#ifndef SORT_H
#define SORT_H

#include <vector>

// wrapping sort to save threshold
class MergeInsertionSorter {
 public:
  size_t threshold{15};

  template <typename T>
  void MergeInsertionSort(std::vector<T>& vec) {
    if (vec.size() <= threshold) {
      for (size_t i = 1; i < vec.size(); ++i) {
        T key = std::move(vec[i]);
        long long j = static_cast<long long>(i) - 1;

        while (j >= 0 && vec[j] > key) {
          vec[j + 1] = std::move(vec[j]);
          --j;
        }

        vec[j + 1] = std::move(key);
      }
      return;
    }

    size_t mid = vec.size() / 2;

    std::vector<T> left{};
    left.reserve(mid);
    std::copy(vec.begin(), vec.begin() + mid, std::back_inserter(left));
    MergeInsertionSort(left);

    std::vector<T> right{};
    right.reserve(mid + 1);
    std::copy(vec.begin() + mid, vec.end(), std::back_inserter(right));
    MergeInsertionSort(right);

    auto cur = vec.begin();
    auto cur_l = left.begin();
    auto cur_r = right.begin();
    for (; cur_l != left.end() && cur_r != right.end(); ++cur) {
      if (*cur_l <= *cur_r) {
        *cur = std::move(*cur_l);
        ++cur_l;
      } else {
        *cur = std::move(*cur_r);
        ++cur_r;
      }
    }

    if (cur_l != left.end()) {
      std::move(cur_l, left.end(), cur);
    } else {
      std::move(cur_r, right.end(), cur);
    }
  }
};

template <typename T>
void MergeSort(std::vector<T>& vec) {
  if (vec.size() <= 1) {
    return;
  }

  size_t mid = vec.size() / 2;

  std::vector<T> left{};
  left.reserve(mid);
  std::copy(vec.begin(), vec.begin() + mid, std::back_inserter(left));
  MergeSort(left);

  std::vector<T> right{};
  right.reserve(mid + 1);
  std::copy(vec.begin() + mid, vec.end(), std::back_inserter(right));
  MergeSort(right);

  auto cur = vec.begin();
  auto cur_l = left.begin();
  auto cur_r = right.begin();
  for (; cur_l != left.end() && cur_r != right.end(); ++cur) {
    if (*cur_l <= *cur_r) {
      *cur = std::move(*cur_l);
      ++cur_l;
    } else {
      *cur = std::move(*cur_r);
      ++cur_r;
    }
  }

  if (cur_l != left.end()) {
    std::move(cur_l, left.end(), cur);
  } else {
    std::move(cur_r, right.end(), cur);
  }
}

#endif