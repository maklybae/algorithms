#include <cassert>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::string s;
  std::getline(std::cin, s);

  std::vector<long long> d1(s.size());
  long long l = 0, r = -1;
  for (long long i = 0; i < s.size(); ++i) {
    long long k = i > r ? 1 : std::min(d1[l + r - i], r - i + 1);
    while (i + k < s.size() && i - k >= 0 && s[i + k] == s[i - k]) {
      ++k;
    }
    d1[i] = k;
    if (i + k - 1 > r) {
      l = i - k + 1;
      r = i + k - 1;
    }
  }

  std::vector<long long> d2(s.size());
  l = 0, r = -1;
  for (long long i = 0; i < s.size(); ++i) {
    long long k = i > r ? 0 : std::min(d2[l + r - i + 1], r - i + 1);
    while (i + k < s.size() && i - k - 1 >= 0 && s[i + k] == s[i - k - 1]) {
      ++k;
    }
    d2[i] = k;
    if (i + k - 1 > r) {
      l = i - k;
      r = i + k - 1;
    }
  }

  long long count = 0;
  for (long long i = 0; i < s.size(); ++i) {
    count += d1[i] + d2[i];
  }

  std::cout << count << '\n';
}
