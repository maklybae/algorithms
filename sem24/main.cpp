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

std::vector<int> ZFunction(std::string_view s) {
  std::vector<int> z(s.size());
  int l = 0, r = 0;
  for (int i = 1; i < s.size(); ++i) {
    z[i] = std::max(0, std::min(r - i, z[i - l]));
    while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]]) {
      ++z[i];
    }
    if (i + z[i] - 1 > r) {
      l = i;
      r = i + z[i] - 1;
    }
  }

  return z;
}

std::string Ptoa(const std::vector<int>& pi) {
  std::string s;
  s.reserve(pi.size());
  char nextChar = 'a';

  for (int i = 0; i < pi.size(); ++i) {
    if (pi[i] == 0) {
      s.push_back(nextChar);
      ++nextChar;
    } else {
      s.push_back(s[pi[i] - 1]);
    }
  }

  return s;
}

std::vector<int> Ptoz(const std::vector<int>& pi) {
  return ZFunction(Ptoa(pi));
}

std::vector<int> Ztop(const std::vector<int>& z) {
  auto n = z.size();
  std::vector<int> pi(n);

  for (int i = 1; i < n; i++) {
    if (z[i]) {
      for (int j = z[i] - 1; j >= 0 && pi[i + j] == 0; j--) {
        pi[i + j] = j + 1;
      }
    }
  }
  return pi;
}

int main() {
  std::string s;
  std::cin >> s;

  std::cout << "Prefix Function:\n";
  std::vector<int> pi = PrefixFunction(s);
  for (auto i : pi) {
    std::cout << i << ' ';
  }
  std::cout << '\n';

  std::cout << "Z Function:\n";
  std::vector<int> z = ZFunction(s);
  for (auto i : z) {
    std::cout << i << ' ';
  }
  std::cout << '\n';

  std::cout << "Ptoa:\n";
  auto s2 = Ptoa(pi);
  std::cout << s2 << '\n';

  std::cout << "Ptoz:\n";
  auto ptoz = Ptoz(pi);
  for (auto i : ptoz) {
    std::cout << i << ' ';
  }
  std::cout << '\n';

  std::cout << "Ztop:\n";
  auto ztop = Ztop(z);
  for (auto i : ztop) {
    std::cout << i << ' ';
  }
  std::cout << '\n';
}
