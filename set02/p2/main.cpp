#include <bit>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

constexpr long long kBase{10000000};
constexpr long long kBaseDigits{7};
using BigInt = std::vector<long long>;

BigInt Parse(std::string a) {
  BigInt res{};
  res.reserve(a.size() / kBaseDigits + 1);
  long long cur_base = 1;
  long long cur_digit = 0;
  for (auto iter = a.rbegin(); iter != a.rend(); ++iter) {
    cur_digit += (*iter - '0') * cur_base;
    cur_base *= 10;

    if (cur_base == kBase) {
      res.emplace_back(cur_digit);
      cur_base = 1;
      cur_digit = 0;
    }
  }
  if (cur_digit != 0) {
    res.emplace_back(cur_digit);
  }
  return res;
}

BigInt NaiveMult(const BigInt& a, const BigInt& b) {
  BigInt res(2 * a.size());

  for (size_t i = 0; i < a.size(); ++i) {
    for (size_t j = 0; j < b.size(); ++j) {
      res[i + j] += a[i] * b[j];
    }
  }

  return res;
}

BigInt DaCMult(const BigInt& a, const BigInt& b) {
  size_t n = a.size();
  if (n <= 128) {
    return NaiveMult(a, b);
  }
  size_t k = n / 2;

  BigInt a_l(a.begin() + k, a.end());
  BigInt a_r(a.begin(), a.begin() + k);
  BigInt b_l(b.begin() + k, b.end());
  BigInt b_r(b.begin(), b.begin() + k);

  BigInt a_lr{};
  a_lr.reserve(k);
  for (size_t i = 0; i < k; ++i) {
    a_lr.emplace_back(a_l[i] + a_r[i]);
  }
  BigInt b_lr{};
  b_lr.reserve(k);
  for (size_t i = 0; i < k; ++i) {
    b_lr.emplace_back(b_l[i] + b_r[i]);
  }

  BigInt p0 = DaCMult(a_r, b_r);
  BigInt p2 = DaCMult(a_l, b_l);

  BigInt p1 = DaCMult(a_lr, b_lr);
  for (size_t i = 0; i < n; ++i) {
    p1[i] -= p0[i];
    p1[i] -= p2[i];
  }

  BigInt res(2 * n);
  std::copy(p0.begin(), p0.end(), res.begin());
  std::copy(p2.begin(), p2.end(), res.begin() + n);
  for (size_t i = k; i < n + k; ++i) {
    res[i] += p1[i - k];
  }

  return res;
}

void Finalize(BigInt& a) {
  if (!a.empty()) {
    for (size_t i = 0; i < a.size() - 1; ++i) {
      a[i + 1] += a[i] / kBase;
      a[i] %= kBase;
    }
    while (!a.empty() && a.back() == 0) {
      a.pop_back();
    }
  }
}

void PrintRes(const BigInt& a) {
  if (a.empty()) {
    std::cout << 0;
    return;
  }

  std::cout.fill('0');
  std::cout << a.back();
  for (auto iter = a.rbegin() + 1; iter != a.rend(); ++iter) {
    std::cout << std::setw(kBaseDigits) << *iter;
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string num1{};
  std::string num2{};
  std::cin >> num1 >> num2;

  auto bi1 = Parse(num1);
  auto bi2 = Parse(num2);
  size_t n = std::bit_ceil(static_cast<size_t>(std::max(bi1.size(), bi2.size())));
  bi1.resize(n);
  bi2.resize(n);

  auto res = DaCMult(bi1, bi2);
  Finalize(res);
  PrintRes(res);
  return 0;
}