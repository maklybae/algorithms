#include <deque>
#include <iostream>
#include <queue>

int main() {
  std::queue<int> first_half{};
  std::deque<int> second_half{};

  int n{};
  std::cin >> n;

  for (int i = 0; i < n; ++i) {
    char command{};
    std::cin >> command;

    if (command == '-') {  // pop command
      std::cout << first_half.front() << '\n';
      first_half.pop();
    } else {  // push commands
      int num{};
      std::cin >> num;

      if (command == '+') {
        second_half.push_back(num);
      } else if (command == '*') {
        second_half.push_front(num);
      }
    }

    if (second_half.size() > first_half.size()) {
      first_half.push(second_half.front());
      second_half.pop_front();
    }
  }

  return 0;
}