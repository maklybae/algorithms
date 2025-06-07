#include <cassert>
#include <compare>
#include <iostream>
#include <queue>
#include <random>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

int main() {
  int n;
  std::cin >> n;
  std::vector<int> encoded(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> encoded[i];
  }

  std::vector<std::string> lzw_table(128);
  for (int i = 0; i < 128; ++i) {
    lzw_table[i] = std::string(1, static_cast<char>(i));
  }

  std::string decoded;
  for (int i = 0; i < n; ++i) {
    int code = encoded[i];
    std::string cur_decoded = lzw_table[code];
    decoded += cur_decoded;

    if (i < n - 1) {
      int next_code = encoded[i + 1];
      std::string next_to_table =
          next_code < lzw_table.size() ? cur_decoded + lzw_table[next_code][0] : cur_decoded + cur_decoded[0];
      lzw_table.push_back(next_to_table);
    }
  }

  std::cout << decoded << '\n';
}