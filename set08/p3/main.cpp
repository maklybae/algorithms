#include <iostream>
#include <string>
#include <string_view>
#include <vector>

std::vector<int> RefinedBorders(std::string_view s) {
  int n = s.size();
  std::vector<int> pi(n + 1, -1);
  for (int i = 1; i <= n; ++i) {
    int j = pi[i - 1];
    while (j != -1 && (s[j] != s[i - 1] /*|| (i < n && s[j + 1] == s[i])*/)) {
      j = pi[j];
    }
    pi[i] = j + 1;
  }
  return pi;
}

int Solve(std::string_view s) {
}

int main() {
  std::string p;
  std::cin >> p;
  std::string t;
  std::cin >> t;

  std::string s = p + '#' + t;
  auto pi = RefinedBorders(s);

  std::vector<int> ind{};
  for (int i = 0; i < t.size(); ++i) {
    if (pi[i + p.size() + 2] == p.size()) {
      ind.push_back(i - p.size());
    }
  }

  std::cout << ind.size() << "\n";
  for (auto i : ind) {
    std::cout << i + 1 << '\n';
  }
}
