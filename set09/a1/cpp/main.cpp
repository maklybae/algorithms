#include <algorithm>
#include <compare>
#include <iostream>
#include <iterator>
#include <map>
#include <random>
#include <string>
#include <string_view>
#include <vector>

using Iterator = std::vector<std::string>::iterator;
using VectorPair = std::vector<std::pair<std::string, int>>;

std::mt19937 kRandom = std::mt19937{std::random_device{}()};

std::pair<std::strong_ordering, int> LcpCompare(const std::string& a, const std::string& b, int k = 0) {
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

void QuickSortHelper(std::vector<std::string>& arr, long long left, long long right, int& cmp_count) {
  if (left >= right) {
    return;
  }

  // Partition
  std::swap(arr[left + kRandom() % (right - left + 1)], arr[right]);
  long long i = left;
  long long j = right - 1;
  while (i <= j) {
    while (true) {
      auto [cmp, k] = LcpCompare(arr[i], arr[right]);
      cmp_count += k;
      if (cmp != std::strong_ordering::less) {
        break;
      }
      ++i;
    }
    while (j > left) {
      auto [cmp, k] = LcpCompare(arr[j], arr[right]);
      cmp_count += k;
      if (cmp == std::strong_ordering::less) {
        break;
      }
      --j;
    }
    if (i >= j) {
      break;
    }
    std::swap(arr[i++], arr[j--]);
  }
  std::swap(arr[i], arr[right]);

  // Recursive calls
  QuickSortHelper(arr, left, i - 1, cmp_count);
  QuickSortHelper(arr, i + 1, right, cmp_count);
}

int QuickSort(std::vector<std::string>& arr) {
  int cmp_count = 0;
  QuickSortHelper(arr, 0, static_cast<long long>(arr.size()) - 1, cmp_count);
  return cmp_count;
}

void MergeSortHelper(std::vector<std::string>& vec, int& cmp_count) {
  if (vec.size() <= 1) {
    return;
  }

  size_t mid = vec.size() / 2;

  std::vector<std::string> left{};
  left.reserve(mid);
  std::copy(vec.begin(), vec.begin() + mid, std::back_inserter(left));
  MergeSortHelper(left, cmp_count);

  std::vector<std::string> right{};
  right.reserve(mid + 1);
  std::copy(vec.begin() + mid, vec.end(), std::back_inserter(right));
  MergeSortHelper(right, cmp_count);

  auto cur = vec.begin();
  auto cur_l = left.begin();
  auto cur_r = right.begin();
  for (; cur_l != left.end() && cur_r != right.end(); ++cur) {
    auto [cmp, k] = LcpCompare(*cur_l, *cur_r);
    cmp_count += k;
    if (cmp != std::strong_ordering::greater) {
      *cur = std::move(*cur_l);
      ++cur_l;
    } else {
      *cur = std::move(*cur_r);
      ++cur_r;
    }
  }

  if (cur_l != left.end()) {
    std::move(cur_l, left.end(), cur);
  } else {
    std::move(cur_r, right.end(), cur);
  }
}

int MergeSort(std::vector<std::string>& vec) {
  int cmp_count = 0;
  MergeSortHelper(vec, cmp_count);
  return cmp_count;
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

class StringGenerator {
 public:
  StringGenerator(int seed, int max_count, double nearly_factor)
      : max_count_(max_count), random_engine_(seed), nearly_factor_(nearly_factor) {
    InitRandom();
    InitReversed();
    InitNearlySorted();
  }

  std::vector<std::string> Random(int count) const {
    std::vector<std::string> result;
    result.insert(result.end(), random_.begin(), std::next(random_.begin(), count));
    return result;
  }

  std::vector<std::string> Reversed(int count) const {
    std::vector<std::string> result;
    result.insert(result.end(), reversed_.begin(), std::next(reversed_.begin(), count));
    return result;
  }

  std::vector<std::string> NearlySorted(int count) const {
    std::vector<std::string> result;
    result.insert(result.end(), nearly_sorted_.begin(), std::next(nearly_sorted_.begin(), count));
    return result;
  }

 private:
  void InitRandom() {
    random_ = GenerateRandomStrings();
  }

  void InitReversed() {
    reversed_ = GenerateRandomStrings();
    std::sort(reversed_.begin(), reversed_.end(), std::greater<>());
  }

  void InitNearlySorted() {
    nearly_sorted_ = GenerateRandomStrings();
    std::sort(nearly_sorted_.begin(), nearly_sorted_.end());

    size_t swaps_count = static_cast<size_t>(nearly_factor_ * static_cast<double>(max_count_));

    while (swaps_count > 0) {
      size_t i = random_engine_() % max_count_;
      size_t j = random_engine_() % max_count_;
      if (i != j) {
        std::swap(nearly_sorted_[i], nearly_sorted_[j]);
        --swaps_count;
      }
    }
  }

  std::string GenerateRandomString() {
    std::string str;
    for (size_t i = 0; i < kMinLength + random_engine_() % (kMaxLength - kMinLength + 1); ++i) {
      str += kAlphabet[random_engine_() % kAlphabet.size()];
    }
    return str;
  }

  std::vector<std::string> GenerateRandomStrings() {
    std::vector<std::string> result;
    result.reserve(max_count_);
    for (size_t i = 0; i < max_count_; ++i) {
      result.emplace_back(GenerateRandomString());
    }
    return result;
  }

  static constexpr std::string_view kAlphabet =
      "!@#%:;^&*()-0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  static constexpr size_t kMinLength = 10;
  static constexpr size_t kMaxLength = 200;

  int max_count_ = 0;
  double nearly_factor_ = 0;
  std::vector<std::string> random_;
  std::vector<std::string> reversed_;
  std::vector<std::string> nearly_sorted_;
  std::mt19937 random_engine_;
};

struct SortTesterResult {
  long long random_time;
  long long reversed_time;
  long long nearly_sorted_time;
};

struct CmpSortTesterResult {
  std::pair<long long, int> random;
  std::pair<long long, int> reversed;
  std::pair<long long, int> nearly_sorted;
};

class SortTester {
 public:
  using Ms = std::chrono::microseconds;

  SortTester(int seed, int max_count, double nearly_factor) : generator_(seed, max_count, nearly_factor) {
  }

  CmpSortTesterResult TestDefaultQuickSort(size_t size) {
    return TestDefault(QuickSort, size);
  }

  CmpSortTesterResult TestDefaultMergeSort(size_t size) {
    return TestDefault(MergeSort, size);
  }

  SortTesterResult TestMsdRadixSort(size_t size) {
    return Test(StringMsdRadixSort, size);
  }

  SortTesterResult TestStringQuickSort(size_t size) {
    return Test(StringQuickSort, size);
  }

  SortTesterResult TestStringMergeSort(size_t size) {
    return Test(StringMergeSort, size);
  }

  SortTesterResult TestStringComboSort(size_t size) {
    return Test(StringComboSort, size);
  }

 private:
  std::pair<long long, int> TestDefault(std::function<int(std::vector<std::string>&)> sort_func,
                                        std::vector<std::string>& data) {
    auto start = std::chrono::high_resolution_clock::now();
    int cmp_count = sort_func(data);
    auto end = std::chrono::high_resolution_clock::now();
    long long time = std::chrono::duration_cast<Ms>(end - start).count();
    return {time, cmp_count};
  }

  CmpSortTesterResult TestDefault(std::function<int(std::vector<std::string>&)> sort_func, size_t size) {
    CmpSortTesterResult result{};
    std::vector<std::string> random = generator_.Random(size);
    std::vector<std::string> reversed = generator_.Reversed(size);
    std::vector<std::string> nearly_sorted = generator_.NearlySorted(size);
    result.random = TestDefault(sort_func, random);
    result.reversed = TestDefault(sort_func, reversed);
    result.nearly_sorted = TestDefault(sort_func, nearly_sorted);
    return result;
  }

  long long Test(std::function<void(std::vector<std::string>&)> sort_func, std::vector<std::string>& data) {
    auto start = std::chrono::high_resolution_clock::now();
    sort_func(data);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<Ms>(end - start).count();
  }

  SortTesterResult Test(std::function<void(std::vector<std::string>&)> sort_func, size_t size) {
    SortTesterResult result{};
    std::vector<std::string> random = generator_.Random(size);
    std::vector<std::string> reversed = generator_.Reversed(size);
    std::vector<std::string> nearly_sorted = generator_.NearlySorted(size);
    result.random_time = Test(sort_func, random);
    result.reversed_time = Test(sort_func, reversed);
    result.nearly_sorted_time = Test(sort_func, nearly_sorted);
    return result;
  }

  StringGenerator generator_;
};

CmpSortTesterResult Average(const CmpSortTesterResult& a, const CmpSortTesterResult& b, const CmpSortTesterResult& c) {
  return {{(a.random.first + b.random.first + c.random.first) / 3,
           (a.random.second + b.random.second + c.random.second) / 3},
          {(a.reversed.first + b.reversed.first + c.reversed.first) / 3,
           (a.reversed.second + b.reversed.second + c.reversed.second) / 3},
          {(a.nearly_sorted.first + b.nearly_sorted.first + c.nearly_sorted.first) / 3,
           (a.nearly_sorted.second + b.nearly_sorted.second + c.nearly_sorted.second) / 3}};
}

SortTesterResult Average(const SortTesterResult& a, const SortTesterResult& b, const SortTesterResult& c) {
  return {(a.random_time + b.random_time + c.random_time) / 3,
          (a.reversed_time + b.reversed_time + c.reversed_time) / 3,
          (a.nearly_sorted_time + b.nearly_sorted_time + c.nearly_sorted_time) / 3};
}

void Print(int n, std::string_view algorithm, const CmpSortTesterResult& result) {
  std::cout << n << ' ' << algorithm << ' ' << "random" << ' ' << result.random.first << ' ' << result.random.second
            << '\n';
  std::cout << n << ' ' << algorithm << ' ' << "reversed" << ' ' << result.reversed.first << ' '
            << result.reversed.second << '\n';
  std::cout << n << ' ' << algorithm << ' ' << "nearly_sorted" << ' ' << result.nearly_sorted.first << ' '
            << result.nearly_sorted.second << '\n';
}

void Print(int n, std::string_view algorithm, const SortTesterResult& result) {
  std::cout << n << ' ' << algorithm << ' ' << "random" << ' ' << result.random_time << '\n';
  std::cout << n << ' ' << algorithm << ' ' << "reversed" << ' ' << result.reversed_time << '\n';
  std::cout << n << ' ' << algorithm << ' ' << "nearly_sorted" << ' ' << result.nearly_sorted_time << '\n';
}

int main() {
  SortTester tester1{0, 3000, 0.3};
  SortTester tester2{0, 3000, 0.3};
  SortTester tester3{0, 3000, 0.3};
  std::cout << "n algorithm array_type time cmp\n";
  for (size_t n = 100; n <= 3000; n += 100) {
    CmpSortTesterResult quick_result =
        Average(tester1.TestDefaultQuickSort(n), tester2.TestDefaultQuickSort(n), tester3.TestDefaultQuickSort(n));
    Print(n, "quick", quick_result);
    CmpSortTesterResult merge_result =
        Average(tester1.TestDefaultMergeSort(n), tester2.TestDefaultMergeSort(n), tester3.TestDefaultMergeSort(n));
    Print(n, "merge", merge_result);

    SortTesterResult msd_radix_result =
        Average(tester1.TestMsdRadixSort(n), tester2.TestMsdRadixSort(n), tester3.TestMsdRadixSort(n));
    Print(n, "msd_radix", msd_radix_result);
    SortTesterResult string_quick_result =
        Average(tester1.TestStringQuickSort(n), tester2.TestStringQuickSort(n), tester3.TestStringQuickSort(n));
    Print(n, "string_quick", string_quick_result);
    SortTesterResult string_merge_result =
        Average(tester1.TestStringMergeSort(n), tester2.TestStringMergeSort(n), tester3.TestStringMergeSort(n));
    Print(n, "string_merge", string_merge_result);
    SortTesterResult string_combo_result =
        Average(tester1.TestStringComboSort(n), tester2.TestStringComboSort(n), tester3.TestStringComboSort(n));
    Print(n, "string_combo", string_combo_result);
  }
}