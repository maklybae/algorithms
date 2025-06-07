#include <cassert>
#include <compare>
#include <iostream>
#include <iterator>
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

void StringQuickSort(std::vector<std::string>& strs) {
  StringQuickSortHelper(strs, 0);
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
  StringQuickSort(strs);
  for (const auto& str : strs) {
    std::cout << str << '\n';
  }
}