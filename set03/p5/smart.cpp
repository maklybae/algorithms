#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

void GetMatrix(long long n, std::vector<std::vector<unsigned long long>>& a) {
  for (long long i = 0; i < n; ++i) {
    std::string row{};
    std::cin >> row;

    a[i].reserve((n + 4 - 1) / 4);
    for (long long j = 0; j < (n + 4 - 1) / 4; ++j) {
      if (row[j] == 'A') {
        a[i].push_back(10);
      } else if (row[j] == 'B') {
        a[i].push_back(11);
      } else if (row[j] == 'C') {
        a[i].push_back(12);
      } else if (row[j] == 'D') {
        a[i].push_back(13);
      } else if (row[j] == 'E') {
        a[i].push_back(14);
      } else if (row[j] == 'F') {
        a[i].push_back(15);
      } else {
        a[i].push_back(row[j] - '0');
      }
    }
  }
}

bool Step(long long n, std::mt19937& rnd, std::vector<std::vector<unsigned long long>>& a,
          std::vector<std::vector<unsigned long long>>& b, std::vector<std::vector<unsigned long long>>& c) {
  std::vector<unsigned long long> vec((n + 4 - 1) / 4);
  for (int i = 0; i < vec.size() - 1; ++i) {
    vec[i] = rnd() % 16;
  }
  long long rem = n % 4;
  if (rem == 0) {
    rem = 4;
  }
  vec[vec.size() - 1] = (rnd() % (1 << rem)) << (4 - rem);

  // c * vec
  std::vector<unsigned long long> cvec(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < (n + 4 - 1) / 4; ++j) {
      cvec[i] += (c[i][j] & vec[j]);
    }
    cvec[i] %= 2;
  }

  // b * vec
  std::vector<unsigned long long> bvec((n + 4 - 1) / 4);
  for (int i = 0; i < n; ++i) {
    unsigned long long tmp = 0;
    for (int j = 0; j < (n + 4 - 1) / 4; ++j) {
      tmp += (b[i][j] & vec[j]);
    }
    bvec[i / 4] += (tmp % 2) * (1 << (3 - i % 4));
  }

  // a * bvec
  std::vector<unsigned long long> abvec(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < (n + 4 - 1) / 4; ++j) {
      abvec[i] += (a[i][j] & bvec[j]);
    }
    abvec[i] %= 2;
  }

  return abvec == cvec;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  long long n{};
  std::cin >> n;

  std::vector<std::vector<unsigned long long>> a(n);
  std::vector<std::vector<unsigned long long>> b(n);
  std::vector<std::vector<unsigned long long>> c(n);

  GetMatrix(n, a);
  GetMatrix(n, b);
  GetMatrix(n, c);

  std::random_device dev{};
  std::mt19937 rnd(dev());
  rnd.seed(31231234);

  for (int i = 0; i < 100000; ++i) {
    if (!Step(n, rnd, a, b, c)) {
      std::cout << "NO";
      return 0;
    }
  }
  std::cout << "YES";
  return 0;
}