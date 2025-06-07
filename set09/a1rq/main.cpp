#include <cassert>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <utility>
#include <vector>

std::mt19937 kRandom = std::mt19937{std::random_device{}()};

void StringQuickSortHelper(std::vector<std::string>& strs, int l) {
  if (strs.size() <= 1) {
    return;
  }

  std::string pivot = strs[kRandom() % strs.size()];

  std::vector<std::string> r_exclude;
  std::vector<std::string> r_equal;
  std::vector<std::string> r_less;
  std::vector<std::string> r_greater;

  for (int i = 0; i < strs.size(); ++i) {
    if (strs[i].size() == l) {
      r_exclude.emplace_back(std::move(strs[i]));
    } else if (strs[i][l] < pivot[l]) {
      r_less.emplace_back(std::move(strs[i]));
    } else if (strs[i][l] > pivot[l]) {
      r_greater.emplace_back(std::move(strs[i]));
    } else {
      r_equal.emplace_back(std::move(strs[i]));
    }
  }

  StringQuickSortHelper(r_less, l);
  StringQuickSortHelper(r_greater, l);
  StringQuickSortHelper(r_equal, l + 1);

  strs.clear();
  strs.insert(strs.end(), std::make_move_iterator(r_exclude.begin()), std::make_move_iterator(r_exclude.end()));
  strs.insert(strs.end(), std::make_move_iterator(r_less.begin()), std::make_move_iterator(r_less.end()));
  strs.insert(strs.end(), std::make_move_iterator(r_equal.begin()), std::make_move_iterator(r_equal.end()));
  strs.insert(strs.end(), std::make_move_iterator(r_greater.begin()), std::make_move_iterator(r_greater.end()));
}

void StringComboSortHelper(std::vector<std::string>& a, int l) {
  if (a.size() < 74) {
    StringQuickSortHelper(a, l);
    return;
  }

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
    StringComboSortHelper(bucket, l + 1);
    a.insert(a.end(), std::make_move_iterator(bucket.begin()), std::make_move_iterator(bucket.end()));
  }
}

void StringComboSort(std::vector<std::string>& a) {
  // std::vector<std::string> aux(a.size());
  // StringMsdRadixSortHelper(a, aux, 0, static_cast<int>(a.size()) - 1, 0);
  StringComboSortHelper(a, 0);
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
  StringComboSort(strs);
  for (const auto& str : strs) {
    std::cout << str << '\n';
  }
}