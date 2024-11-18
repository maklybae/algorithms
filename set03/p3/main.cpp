#include <iostream>
#include <queue>
#include <vector>

const long long BASE = 256;

void radixSort(std::vector<long long>& arr) {
  std::vector<std::queue<long long>> queues(BASE);

  long long cur_base = 1;
  for (int iteration = 0; iteration < 4; ++iteration) {
    for (size_t i = 0; i < arr.size(); ++i) {
      queues[std::abs(arr[i]) / cur_base % BASE].push(arr[i]);
    }
    arr.clear();
    for (auto& queue : queues) {
      while (!queue.empty()) {
        arr.push_back(queue.front());
        queue.pop();
      }
    }
    cur_base *= BASE;
  }

  std::queue<long long> neg{};
  std::queue<long long> pos{};
  for (size_t i = 0; i < arr.size(); ++i) {
    if (arr[i] < 0) {
      neg.push(arr[i]);
    } else {
      pos.push(arr[i]);
    }
  }
  for (long long i = neg.size() - 1; i >= 0; --i) {
    arr[i] = neg.front();
    neg.pop();
  }
  for (size_t i = arr.size() - pos.size(); i < arr.size(); ++i) {
    arr[i] = pos.front();
    pos.pop();
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  size_t n{};
  std::cin >> n;

  std::vector<long long> arr(n);

  for (size_t i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }

  radixSort(arr);

  for (size_t i = 0; i < arr.size(); ++i) {
    std::cout << arr[i] << ' ';
  }
}