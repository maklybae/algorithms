#include <iostream>
#include <string>
#include <string_view>
#include <vector>

int Solve(std::string_view s) {
  std::vector<int> pi(s.size() + 1);
  int mx = -1;
  pi[0] = -1;
  for (int i = 1; i <= s.size(); ++i) {
    int j = pi[i - 1];
    while (j != -1 && s[j] != s[i - 1]) {
      j = pi[j];
    }
    pi[i] = j + 1;
    mx = std::max(mx, pi[i]);
  }
  return s.size() - mx;
}

int main() {
  std::string s;
  std::cin >> s;
  std::cout << Solve(s) << "\n";
}