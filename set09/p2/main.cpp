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
  std::string s;
  std::getline(std::cin, s);

  std::unordered_map<std::string, int> lzw_table;
  for (int i = 0; i < 128; ++i) {
    lzw_table[std::string(1, static_cast<char>(i))] = i;
  }

  std::string prev(1, s[0]);
  std::string cur;
  std::vector<int> output_code;
  int code = 128;
  for (int i = 0; i < s.size(); ++i) {
    if (i != s.length() - 1) {
      cur += s[i + 1];
    }
    if (lzw_table.contains(prev + cur)) {
      prev += cur;
    } else {
      output_code.push_back(lzw_table[prev]);
      lzw_table[prev + cur] = code++;
      prev = cur;
    }
    cur.clear();
  }
  if (!prev.empty()) {
    output_code.push_back(lzw_table[prev]);
  }

  std::cout << output_code.size() << '\n';
  for (const auto& code : output_code) {
    std::cout << code << ' ';
  }
}