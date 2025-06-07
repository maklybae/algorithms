#include <cassert>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

std::vector<long long> prev(4010, 0), curr(4010, 0);

long long LevenshteinDistance(std::string_view s1, std::string_view s2) {
  int len1 = s1.length();
  int len2 = s2.length();

  for (int j = 0; j <= len2; ++j) {
    prev[j] = j;
  }

  for (int i = 1; i <= len1; ++i) {
    curr[0] = i;
    for (int j = 1; j <= len2; ++j) {
      if (s1[i - 1] == s2[j - 1]) {
        curr[j] = prev[j - 1];
      } else {
        curr[j] = prev[j - 1] + 1;  // Replacement
      }
      curr[j] = std::min(curr[j], std::min(prev[j] + 1, curr[j - 1] + 1));  // Deletion and Insertion
    }
    std::swap(prev, curr);
  }
  return prev[len2];
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n;
  std::cin >> n;
  std::cin.ignore();
  for (int i = 0; i < n; ++i) {
    std::string s1, s2;
    std::getline(std::cin, s1);
    std::getline(std::cin, s2);

    std::cout << LevenshteinDistance(s1, s2) << ' ';
  }
}
