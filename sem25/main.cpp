#include <iostream>
#include <string>
#include <string_view>
#include <vector>

int DamerauLevenshteinDistance(std::string_view s1, std::string_view s2) {
  int len1 = s1.length();
  int len2 = s2.length();

  std::vector<std::vector<int>> d(len1 + 1, std::vector<int>(len2 + 1));
  for (int i = 0; i <= len1; ++i) {
    d[i][0] = i;
  }
  for (int j = 0; j <= len2; ++j) {
    d[0][j] = j;
  }

  for (int i = 1; i <= len1; ++i) {
    for (int j = 1; j <= len2; ++j) {
      if (s1[i - 1] == s2[j - 1]) {
        d[i][j] = d[i - 1][j - 1];
      } else {
        d[i][j] = d[i - 1][j - 1] + 1;  // Replacement
      }
      d[i][j] = std::min(d[i][j], std::min(d[i - 1][j] + 1, d[i][j - 1] + 1));  // Deletion and Insertion
      if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
        d[i][j] = std::min(d[i][j], d[i - 2][j - 2] + 1);  // Transposition
      }
    }
  }

  return d[len1][len2];
}

int main() {
  {
    std::string s1 = "KACO";
    std::string s2 = "BKAOC";
    int distance = DamerauLevenshteinDistance(s1, s2);
    std::cout << "Damerau-Levenshtein distance between \"" << s1 << "\" and \"" << s2 << "\" is: " << distance << '\n';
  }
  {
    std::string s1 = "CA";
    std::string s2 = "ABC";
    int distance = DamerauLevenshteinDistance(s1, s2);
    std::cout << "Damerau-Levenshtein distance between \"" << s1 << "\" and \"" << s2 << "\" is: " << distance << '\n';
    // Output: 3
    // Использование этого упрощённого алгоритма накладывает ограничение: любая подстрока может быть редактирована не
    // более одного раза. Переход AC->ABC невозможен (в упрощённом алгоритме нельзя вставить символ "между" уже
    // существующими символами, если они были получены в результате транспозиции)
    // Будет такая последовательность CA->A->AB->ABC
  }
  {
    std::string s1 = "ABOBA";
    std::string s2 = "BOBAC";
    int distance = DamerauLevenshteinDistance(s1, s2);
    std::cout << "Damerau-Levenshtein distance between \"" << s1 << "\" and \"" << s2 << "\" is: " << distance << '\n';
  }
}