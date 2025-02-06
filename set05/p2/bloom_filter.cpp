#include "bloom_filter.h"

BloomFilter::BloomFilter(size_t hashes, size_t bits)
    : _hashes(hashes), _bits(bits), cnt(0), false_positive_cnt(0), _filter(bits) {
}

void BloomFilter::add(const std::string &str) {
  for (int i = 0; i < _hashes; ++i) {
    auto hash = _get_hash(i, str) % _bits;
    _filter[hash] = true;
  }
  _raw_set.emplace(str);
}

bool BloomFilter::verify(const std::string &str) {
  ++cnt;
  for (int i = 0; i < _hashes; ++i) {
    auto hash = _get_hash(i, str) % _bits;
    if (!_filter[hash]) {
      return false;
    }
  }
  if (!_raw_set.contains(str)) {
    ++false_positive_cnt;
  }
  return true;
}

double BloomFilter::getFPRate() const {
  if (cnt == 0) {
    return 0;
  }
  return static_cast<double>(false_positive_cnt) / cnt;
}

size_t BloomFilter::numberOfHashFunctions() const {
  return _hashes;
}

size_t BloomFilter::numberOfBits() const {
  return _bits;
}

inline size_t BloomFilter::_get_hash(int i, const std::string &str) const {
  if (i == 0) {
    return hasher(str);
  }
  return hasher(str + std::to_string(i));
}