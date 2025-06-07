#include <iostream>
#include <string>
#include <string_view>
#include <vector>

std::vector<int> BMTable(std::string_view p) {
  std::vector<int> bm(26, p.size());
  for (int i = p.size() - 2; i >= 0; --i) {
    if (bm[p[i] - 'a'] == p.size()) {
      bm[p[i] - 'a'] = p.size() - i - 1;
    }
  }
  return bm;
}

int main() {
  std::string p;
  std::cin >> p;
  std::string t;
  std::cin >> t;

  std::vector<int> ind{};
  std::vector<int> bm = BMTable(p);
  for (int i = p.size() - 1; i < t.size();) {
    // Расхождение в первом символе
    if (t[i] != p[p.size() - 1]) {
      i += bm[t[i] - 'a'];
      continue;
    }

    int j = p.size() - 2;
    while (j >= 0 && t[i - p.size() + 1 + j] == p[j]) {
      --j;
    }
    if (j < 0) {
      ind.push_back(i - p.size() + 1);
      i++;
    } else {
      i += bm[p[j] - 'a'];
    }
  }

  std::cout << ind.size() << std::endl;
  for (int i = 0; i < ind.size(); ++i) {
    std::cout << ind[i] << '\n';
  }
}
