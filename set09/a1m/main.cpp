#include <cassert>
#include <compare>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using Iterator = std::vector<std::string>::iterator;
using VectorPair = std::vector<std::pair<std::string, int>>;

std::pair<std::strong_ordering, int> LcpCompare(const std::string& a, const std::string& b, int k) {
  for (int i = k; i < std::min(a.size(), b.size()); ++i) {
    if (a[i] != b[i]) {
      return {a[i] <=> b[i], i};
    }
  }
  if (a.size() == b.size()) {
    return {std::strong_ordering::equal, static_cast<int>(a.size())};
  }
  if (a.size() < b.size()) {
    return {std::strong_ordering::less, static_cast<int>(a.size())};
  }
  return {std::strong_ordering::greater, static_cast<int>(b.size())};
}

VectorPair Merge(VectorPair& left, VectorPair& right) {
  VectorPair result;
  result.reserve(left.size() + right.size());

  auto it_left = left.begin();
  auto it_right = right.begin();
  while (it_left != left.end() && it_right != right.end()) {
    if (it_left->second > it_right->second) {
      result.emplace_back(*it_left);
      ++it_left;
    } else if (it_left->second < it_right->second) {
      result.emplace_back(*it_right);
      ++it_right;
    } else {
      auto [cmp, k] = LcpCompare(it_left->first, it_right->first, 0);
      if (cmp == std::strong_ordering::less) {
        result.emplace_back(*it_left);
        ++it_left;
        it_right->second = k;
      } else {
        result.emplace_back(*it_right);
        ++it_right;
        it_left->second = k;
      }
    }
  }

  while (it_left != left.end()) {
    result.emplace_back(*it_left);
    ++it_left;
  }
  while (it_right != right.end()) {
    result.emplace_back(*it_right);
    ++it_right;
  }
  return result;
}

VectorPair StringMergeSortHelper(Iterator begin, Iterator end) {
  if (std::next(begin) == end) {
    return {{*begin, 1}};
  }

  Iterator mid = begin + (end - begin) / 2;
  auto left = StringMergeSortHelper(begin, mid);
  auto right = StringMergeSortHelper(mid, end);

  return Merge(left, right);
}

void StringMergeSort(std::vector<std::string>& strs) {
  if (strs.size() <= 1) {
    return;
  }
  auto result = StringMergeSortHelper(strs.begin(), strs.end());
  strs.clear();
  for (const auto& [str, k] : result) {
    strs.emplace_back(str);
  }
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
  StringMergeSort(strs);
  for (const auto& str : strs) {
    std::cout << str << '\n';
  }
}