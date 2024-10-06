#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

constexpr long long kBase{100};
constexpr long long kBaseDigits{2};
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

BigInt Mult(const BigInt& a, const BigInt& b) {
  BigInt res(a.size() + b.size());

  for (size_t i = 0; i < a.size(); ++i) {
    for (size_t j = 0; j < b.size(); ++j) {
      res[i + j] += a[i] * b[j];
    }
  }

  if (!res.empty()) {
    for (size_t i = 0; i < res.size() - 1; ++i) {
      res[i + 1] += res[i] / kBase;
      res[i] %= kBase;
    }
    while (!res.empty() && res.back() == 0) {
      res.pop_back();
    }
  }

  return res;
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
  auto res = Mult(bi1, bi2);

  PrintRes(res);
  return 0;
}