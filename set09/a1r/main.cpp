#include <cassert>
#include <compare>
#include <iostream>
#include <iterator>
#include <map>
#include <random>
#include <string>
#include <utility>
#include <vector>

void StringMsdRadixSortHelperIndices(std::vector<std::string>& a, std::vector<std::string>& aux, int lo, int hi,
                                     int d) {
  if (hi <= lo) {
    return;
  }
  const int R = 256;  // ASCII alphabet size
  std::vector<int> count(R + 2, 0);

  for (int i = lo; i <= hi; ++i) {
    int c = d < a[i].size() ? static_cast<char>(a[i][d]) : -1;
    count[c + 2]++;
  }
  // prefix
  for (int r = 0; r < R + 1; ++r) {
    count[r + 1] += count[r];
  }

  for (int i = lo; i <= hi; ++i) {
    int c = d < a[i].size() ? static_cast<char>(a[i][d]) : -1;
    aux[count[c + 1]++] = std::move(a[i]);
  }
  for (int i = lo; i <= hi; ++i) {
    a[i] = std::move(aux[i - lo]);
  }

  for (int r = 0; r < R; ++r) {
    StringMsdRadixSortHelperIndices(a, aux, lo + count[r], lo + count[r + 1] - 1, d + 1);
  }
}

void StringMsdRadixSortHelperVectors(std::vector<std::string>& a, int l) {
  std::map<char, std::vector<std::string>> buckets;
  for (const auto& str : a) {
    if (l < str.size()) {
      buckets[str[l]].emplace_back(std::move(str));
    } else {
      buckets[-1].emplace_back(std::move(str));  // -1 for strings shorter than l
    }
  }
  a.clear();
  a.insert(a.end(), std::make_move_iterator(buckets[-1].begin()), std::make_move_iterator(buckets[-1].end()));

  for (auto& [c, bucket] : buckets) {
    if (c == -1) {
      continue;  // Skip the -1 bucket
    }
    StringMsdRadixSortHelperVectors(bucket, l + 1);
    a.insert(a.end(), std::make_move_iterator(bucket.begin()), std::make_move_iterator(bucket.end()));
  }
}

void StringMsdRadixSort(std::vector<std::string>& a) {
  // std::vector<std::string> aux(a.size());
  // StringMsdRadixSortHelper(a, aux, 0, static_cast<int>(a.size()) - 1, 0);
  StringMsdRadixSortHelperVectors(a, 0);
}

int main() {
  int n;
  std::cin >> n;
  std::cin.ignore();
  std::vector<std::string> strs;
  strs.reserve(n);
  for (int i = 0; i < n; ++i) {
    std::string s;
    std::getline(std::cin, s);
    strs.emplace_back(std::move(s));
  }
  StringMsdRadixSort(strs);
  for (const auto& str : strs) {
    std::cout << str << '\n';
  }
}