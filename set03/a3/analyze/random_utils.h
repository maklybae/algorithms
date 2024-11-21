#ifndef RANDOM_UTILS_H
#define RANDOM_UTILS_H

#include <random>

inline std::mt19937& GetRandomEngine() {
  static thread_local std::mt19937 engine{std::random_device{}()};
  return engine;
}

#endif