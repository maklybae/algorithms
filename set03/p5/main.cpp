#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

void ReadMatrix(std::vector<std::vector<bool>>& a) {
  for (long long i = 0; i < a.size(); ++i) {
    std::string row{};
    std::cin >> row;

    for (long long j = 0; j < (a.size() + 4 - 1) / 4; ++j) {
      int num{};
      if (row[j] == 'A') {
        num = 10;
      } else if (row[j] == 'B') {
        num = 11;
      } else if (row[j] == 'C') {
        num = 12;
      } else if (row[j] == 'D') {
        num = 13;
      } else if (row[j] == 'E') {
        num = 14;
      } else if (row[j] == 'F') {
        num = 15;
      } else {
        num = row[j] - '0';
      }

      for (int k = 3; k >= 0; --k) {
        if (4 * j + k < a.size()) {
          a[i][4 * j + k] = num % 2;
        }
        num /= 2;
      }
    }
  }
}

bool Check(std::vector<bool> vec, std::vector<std::vector<bool>>& a, std::vector<std::vector<bool>>& b,
           std::vector<std::vector<bool>>& c) {
  std::vector<bool> cvec(vec.size());
  for (int i = 0; i < vec.size(); ++i) {
    for (int j = 0; j < vec.size(); ++j) {
      cvec[i] = (static_cast<int>(cvec[i]) + (c[i][j] & vec[j])) % 2;
    }
  }

  std::vector<bool> bvec(vec.size());
  for (int i = 0; i < vec.size(); ++i) {
    for (int j = 0; j < vec.size(); ++j) {
      bvec[i] = (static_cast<int>(bvec[i]) + (b[i][j] & vec[j])) % 2;
    }
  }

  std::vector<bool> abvec(vec.size());
  for (int i = 0; i < vec.size(); ++i) {
    for (int j = 0; j < vec.size(); ++j) {
      abvec[i] = (static_cast<int>(abvec[i]) + (a[i][j] & bvec[j])) % 2;
    }
  }

  return abvec == cvec;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  long long n{};
  std::cin >> n;

  std::random_device dev{};
  std::mt19937 rnd(dev());
  rnd.seed(31231234);

  std::vector<std::vector<bool>> a(n, std::vector<bool>(n));
  std::vector<std::vector<bool>> b(n, std::vector<bool>(n));
  std::vector<std::vector<bool>> c(n, std::vector<bool>(n));

  ReadMatrix(a);
  ReadMatrix(b);
  ReadMatrix(c);

  for (int i = 0; i < 20; ++i) {
    std::vector<bool> vec(n);
    for (int j = 0; j < n; ++j) {
      vec[j] = rnd() % 2;
    }

    if (!Check(vec, a, b, c)) {
      std::cout << "NO";
      return 0;
    }
  }

  std::cout << "YES";
  return 0;
}