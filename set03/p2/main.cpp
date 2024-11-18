#include <iostream>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  size_t n{};
  std::cin >> n;

  std::vector<long long> memory(2000001);

  for (long long i = 0; i < n; ++i) {
    long long cur{};
    std::cin >> cur;
    ++memory[cur + 1000000];
  }

  for (long long i = 0; i < memory.size(); ++i) {
    for (long long j = 0; j < memory[i]; ++j) {
      std::cout << i - 1000000 << ' ';
    }
  }
}