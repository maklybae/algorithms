#include "generator.h"

#include "random_utils.h"

std::vector<int> ArrayGenerator::GenerateRandomVec() {
  auto random_engine = GetRandomEngine();
  std::uniform_int_distribution distr{min_val_, max_val_};
  std::vector<int> result{};
  result.reserve(max_size_);
  for (size_t i = 0; i < max_size_; ++i) {
    result.push_back(distr(random_engine));
  }

  return result;
}

void ArrayGenerator::InitRandom() {
  random_ = GenerateRandomVec();
}
void ArrayGenerator::InitReversed() {
  reversed_ = GenerateRandomVec();
  std::sort(reversed_.begin(), reversed_.end(), std::greater<>());
}
void ArrayGenerator::InitNearlySorted() {
  nearly_sorted_ = GenerateRandomVec();
  std::sort(nearly_sorted_.begin(), nearly_sorted_.end());

  auto random_engine = GetRandomEngine();
  size_t swaps_count = static_cast<size_t>(nearly_factor_ * static_cast<double>(max_size_));
  while (swaps_count > 0) {
    size_t i = random_engine() % max_size_;
    size_t j = random_engine() % max_size_;
    if (i != j) {
      std::swap(nearly_sorted_[i], nearly_sorted_[j]);
      --swaps_count;
    }
  }
}

ArrayGenerator::ArrayGenerator(int mn, int mx, size_t max_size, double nearly_factor)
    : min_val_{mn}, max_val_{mx}, max_size_{max_size}, nearly_factor_{nearly_factor} {
  InitRandom();
  InitReversed();
  InitNearlySorted();
}

std::vector<int> ArrayGenerator::Random(size_t size) {
  std::vector<int> result(size);
  std::copy_n(random_.begin(), size, result.begin());
  return result;
}
std::vector<int> ArrayGenerator::Reversed(size_t size) {
  std::vector<int> result(size);
  std::copy_n(reversed_.begin(), size, result.begin());
  return result;
}
std::vector<int> ArrayGenerator::NearlySorted(size_t size) {
  std::vector<int> result(size);
  std::copy_n(nearly_sorted_.begin(), size, result.begin());
  return result;
}
