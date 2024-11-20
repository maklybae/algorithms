#include <iostream>
#include <vector>

template <typename T>
void InsertionSort(std::vector<T>& vec) {
  for (size_t i = 1; i < vec.size(); ++i) {
    T key = std::move(vec[i]);
    long long j = static_cast<long long>(i) - 1;

    while (j >= 0 && vec[j] > key) {
      vec[j + 1] = std::move(vec[j]);
      --j;
    }

    vec[j + 1] = std::move(key);
  }
}

template <typename T>
void MergeSort(std::vector<T>& vec) {
  if (vec.size() <= 15) {
    InsertionSort(vec);
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

int main() {
  size_t n{};
  std::cin >> n;

  std::vector<int> vec{};
  vec.reserve(n);

  for (size_t i = 0; i < n; ++i) {
    int t{};
    std::cin >> t;
    vec.push_back(t);
  }

  MergeSort(vec);
  for (size_t i = 0; i < n; ++i) {
    std::cout << vec[i] << ' ';
  }

  return 0;
}