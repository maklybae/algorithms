#include <iostream>
#include <utility>
#include <vector>

using Matrix = std::vector<std::vector<long long>>;
using Offset = std::pair<size_t, size_t>;

// Matrix CopyMatrix(const Matrix& a, std::pair<size_t, size_t> from, std::pair<size_t, size_t> to) {
//   size_t k = to.first - from.first;
//   std::vector<std::vector<long long>> res{};
//   res.reserve(k);
//   for (size_t i = from.first; i < to.first; ++i) {
//     res.emplace_back();
//     std::copy(a[i].begin() + from.second, a[i].begin() + to.second, std::back_inserter(res.back()));
//   }
//   return res;
// }

Matrix SumMatrix(const Matrix& a, const Matrix& b) {
  Matrix c{};
  c.reserve(a.size());
  for (size_t i = 0; i < a.size(); ++i) {
    c.emplace_back();
    c.back().reserve(a.size());
    for (size_t j = 0; j < b.size(); ++j) {
      c.back().emplace_back(a[i][j] + b[i][j]);
    }
  }
  return c;
}

Matrix MultMatrixDaC(const Matrix& a, Offset a_offset, const Matrix& b, Offset b_offset, size_t n) {
  if (n <= 32) {
    Matrix res{};
    res.reserve(n);

    for (size_t i = 0; i < n; ++i) {
      res.emplace_back();
      res.back().reserve(n);
      for (int j = 0; j < n; ++j) {
        long long cur{};
        for (int k = 0; k < n; ++k) {
          cur += a[a_offset.first + i][a_offset.second + k] * b[b_offset.first + k][b_offset.second + j];
        }
        res.back().emplace_back(cur);
      }
    }

    return res;
  }

  size_t mid{n / 2};
  auto a_offset_00 = Offset{a_offset.first, a_offset.second};
  auto a_offset_01 = Offset{a_offset.first, a_offset.second + mid};
  auto a_offset_10 = Offset{a_offset.first + mid, a_offset.second};
  auto a_offset_11 = Offset{a_offset.first + mid, a_offset.second + mid};
  auto b_offset_00 = Offset{b_offset.first, b_offset.second};
  auto b_offset_01 = Offset{b_offset.first, b_offset.second + mid};
  auto b_offset_10 = Offset{b_offset.first + mid, b_offset.second};
  auto b_offset_11 = Offset{b_offset.first + mid, b_offset.second + mid};

  auto c00 =
      SumMatrix(MultMatrixDaC(a, a_offset_00, b, b_offset_00, mid), MultMatrixDaC(a, a_offset_01, b, b_offset_10, mid));
  auto c01 =
      SumMatrix(MultMatrixDaC(a, a_offset_00, b, b_offset_01, mid), MultMatrixDaC(a, a_offset_01, b, b_offset_11, mid));
  auto c10 =
      SumMatrix(MultMatrixDaC(a, a_offset_10, b, b_offset_00, mid), MultMatrixDaC(a, a_offset_11, b, b_offset_10, mid));
  auto c11 =
      SumMatrix(MultMatrixDaC(a, a_offset_10, b, b_offset_01, mid), MultMatrixDaC(a, a_offset_11, b, b_offset_11, mid));

  Matrix res{};
  res.reserve(n);
  for (size_t i = 0; i < n; ++i) {
    res.emplace_back();
    res.back().reserve(n);
    if (i < mid) {
      std::copy((c00.begin() + i)->begin(), (c00.begin() + i)->end(), std::back_inserter(res.back()));
      std::copy((c01.begin() + i)->begin(), (c01.begin() + i)->end(), std::back_inserter(res.back()));
    } else {
      std::copy((c10.begin() + (i - mid))->begin(), (c10.begin() + (i - mid))->end(), std::back_inserter(res.back()));
      std::copy((c11.begin() + (i - mid))->begin(), (c11.begin() + (i - mid))->end(), std::back_inserter(res.back()));
    }
  }

  return res;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  size_t n{};
  std::cin >> n;

  if (n == 1) {
    long long a{};
    long long b{};
    std::cin >> a >> b;
    std::cout << a * b << '\n';
    return 0;
  }

  Matrix a{};
  a.reserve(n);
  for (size_t i = 0; i < n; ++i) {
    a.emplace_back();
    a.back().reserve(n);
    for (size_t j = 0; j < n; ++j) {
      long long tmp{};
      std::cin >> tmp;
      a.back().push_back(tmp);
    }
  }

  Matrix b{};
  b.reserve(n);
  for (size_t i = 0; i < n; ++i) {
    b.emplace_back();
    b.back().reserve(n);
    for (size_t j = 0; j < n; ++j) {
      long long tmp{};
      std::cin >> tmp;
      b.back().push_back(tmp);
    }
  }

  auto res = MultMatrixDaC(a, {0, 0}, b, {0, 0}, n);
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      std::cout << res[i][j] << ' ';
    }
    std::cout << '\n';
  }
  return 0;
}