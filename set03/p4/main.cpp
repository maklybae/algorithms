#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

struct Frac {
  long long num{};
  long long den{};
};

bool operator<=(Frac a, Frac b) {
  if (a.den < 0) {
    a.num = -a.num;
    a.den = -a.den;
  }
  if (b.den < 0) {
    b.num = -b.num;
    b.den = -b.den;
  }

  return a.num * b.den <= a.den * b.num;
}

void MergeSort(std::vector<Frac>& vec) {
  if (vec.size() <= 1) {
    return;
  }

  size_t mid = vec.size() / 2;

  std::vector<Frac> left{};
  left.reserve(mid);
  std::copy(vec.begin(), vec.begin() + mid, std::back_inserter(left));
  MergeSort(left);

  std::vector<Frac> right{};
  right.reserve(mid + 1);
  std::copy(vec.begin() + mid, vec.end(), std::back_inserter(right));
  MergeSort(right);

  auto cur = vec.begin();
  auto cur_l = left.begin();
  auto cur_r = right.begin();
  for (; cur_l != left.end() && cur_r != right.end(); ++cur) {
    if (*cur_l <= *cur_r) {
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

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  size_t n{};
  std::cin >> n;

  std::vector<Frac> arr;
  arr.reserve(n);
  for (size_t i = 0; i < n; ++i) {
    std::string frac_str{};
    std::cin >> frac_str;
    std::stringstream stream(frac_str);

    std::string num_str{};
    std::getline(stream, num_str, '/');
    std::string den_str{};
    std::getline(stream, den_str, '/');

    Frac frac{};
    frac.num = std::stoll(num_str);
    frac.den = std::stoll(den_str);

    arr.push_back(frac);
  }

  MergeSort(arr);

  for (size_t i = 0; i < arr.size(); ++i) {
    std::cout << arr[i].num << '/' << arr[i].den << ' ';
  }
}