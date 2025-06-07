#include <iostream>
#include <string>
#include <string_view>
#include <vector>

std::vector<int> PrefixFunction(std::string_view s) {
  std::vector<int> pi(s.size() + 1);
  pi[0] = -1;
  for (int i = 1; i <= s.size(); ++i) {
    int j = pi[i - 1];
    while (j != -1 && s[j] != s[i - 1]) {
      j = pi[j];
    }
    pi[i] = j + 1;
  }
  auto res = std::vector<int>(pi.begin() + 1, pi.end());
  return res;
}

int main() {
  std::string s;
  std::cin >> s;
  auto pi = PrefixFunction(s);
  for (int i = 0; i < pi.size(); ++i) {
    std::cout << pi[i] << " ";
  }
  std::cout << "\n";
}