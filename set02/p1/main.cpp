#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

struct Interval {
  int left{};
  int right{};

  size_t length() const;
  Interval overlap(const Interval& other);
};

size_t Interval::length() const {
  return right - left;
}

Interval Interval::overlap(const Interval& other) {
  if (other.right <= left || other.left >= right) {
    return {};
  }
  return {std::max(left, other.left), std::min(right, other.right)};
}

void MergeSort(std::vector<Interval>& vec) {
  if (vec.size() <= 1) {
    return;
  }

  size_t mid = vec.size() / 2;

  std::vector<Interval> left{};
  left.reserve(mid);
  std::copy(vec.begin(), vec.begin() + mid, std::back_inserter(left));
  MergeSort(left);

  std::vector<Interval> right{};
  right.reserve(mid + 1);
  std::copy(vec.begin() + mid, vec.end(), std::back_inserter(right));
  MergeSort(right);

  auto cur = vec.begin();
  auto cur_l = left.begin();
  auto cur_r = right.begin();
  for (; cur_l != left.end() && cur_r != right.end(); ++cur) {
    if (cur_l->left == cur_r->left) {
      if (cur_l->right < cur_r->right) {
        *cur = *cur_l;
        ++cur_l;
      } else {
        *cur = *cur_r;
        ++cur_r;
      }
    } else if (cur_l->left < cur_r->left) {
      *cur = *cur_l;
      ++cur_l;
    } else {
      *cur = *cur_r;
      ++cur_r;
    }
  }

  if (cur_l != left.end()) {
    std::copy(cur_l, left.end(), cur);
  } else {
    std::copy(cur_r, right.end(), cur);
  }
}

Interval FindPairOverlapDaC(std::vector<Interval>& vec, size_t first, size_t last) {
  if (last - first <= 1) {
    return {};
  }
  size_t mid = (first + last) / 2;
  auto left_res = FindPairOverlapDaC(vec, first, mid);
  auto right_res = FindPairOverlapDaC(vec, mid, last);

  auto res =
      std::max(left_res, right_res, [](const Interval& x, const Interval& y) { return x.length() < y.length(); });

  // find max right from left
  int left_max_right = INT_MIN;

  for (size_t i = first; i < mid; ++i) {
    if (vec[i].right > left_max_right) {
      left_max_right = vec[i].right;
    }
  }

  if (vec[mid].left >= left_max_right) {
    return res;
  }

  Interval imaginary{vec[mid].left, left_max_right};
  for (size_t i = mid; i < last; ++i) {
    res = std::max(res, imaginary.overlap(vec[i]),
                   [](const Interval& x, const Interval& y) { return x.length() < y.length(); });
  }
  return res;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  size_t n{};
  std::cin >> n;
  std::vector<Interval> vec{};
  vec.reserve(n);
  for (size_t i = 0; i < n; ++i) {
    int left{};
    int right{};
    std::cin >> left >> right;
    vec.emplace_back(left, right + 1);
  }

  MergeSort(vec);
  auto ans = FindPairOverlapDaC(vec, 0, vec.size());
  std::cout << ans.length() << '\n';
  if (ans.length() > 0) {
    std::cout << ans.left << ' ' << ans.right - 1 << '\n';
  }

  return 0;
}